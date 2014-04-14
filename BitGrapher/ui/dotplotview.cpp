#include "ui/dotplotview.h"

DotPlotView::DotPlotView(QWidget *parent) :
    QWidget(parent)
{
}

void DotPlotView::setDiagonals(std::list<Diagonal> const sd, unsigned int w, unsigned int h)
{
    m_listDiag = sd;
    m_height = h;
    m_width = w;
}

void DotPlotView::setDiagonals(std::list<Diagonal> const sd)
{
    m_listDiag = sd;
}
void DotPlotView::setBitString(BitString const* b){
    m_bitstring = b;
    m_height = b->size();
    m_width = b->size();
    m_listDiag = b->dotPlotPattern();
}

void DotPlotView::setBitStrings(BitString const* b1, BitString const* b2){
    m_bitstring = b1;
    m_bitstring2 = b2;
    m_height = b2->size();
    m_width = b1->size();
    m_listDiag = b1->dotPlotPattern(b2);
}

void DotPlotView::paintEvent(QPaintEvent* /* event */)
{
    int border = 15;
    int width = this->width() - border;
    int height = this->height() - border;
    qreal mw = width / m_width;
    qreal mh = height / m_height;

    QPainter painter(this);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    pen.setBrush(Qt::blue);
    painter.setPen(pen);
    painter.setFont(QFont("Arial", this->width()/m_bitstring->size()));
    painter.drawText(border, 10, QString(m_bitstring->toString().c_str()));

    painter.setFont(QFont("Arial", this->height()/m_bitstring2->size()));
    painter.rotate(90);
    painter.drawText(border, 0, QString(m_bitstring2->toString().c_str()));
    painter.rotate(-90);

    for (std::list<Diagonal>::iterator it = m_listDiag.begin(); it != m_listDiag.end(); ++it){
        unsigned int x = (*it).getX();
        unsigned int y = (*it).getY();
        unsigned int l = (*it).length();
        painter.drawLine(border + x*mw, border + y*mh, border + (x+l)*mw, border + (y+l)*mh);
        std::cout << "Diag " << (*it).toString() << std::endl ;
    }

    //debug
    /*std::cout << "<----------------------ListDiag--------------------------->" << std::endl;
    for (std::list<Diagonal>::iterator i = m_listDiag.begin(); i != m_listDiag.end(); i++ ){
        std::cout << "Diag " << (*i).toString() << std::endl ;
    }*/

}
