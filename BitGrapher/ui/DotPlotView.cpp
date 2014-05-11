#include "DotPlotView.h"

DotPlotView::DotPlotView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DotPlotView),
    m_classicPen(new QPen(Qt::blue)),
    m_selectedPen(new QPen(Qt::red))
{
    ui->setupUi(this);
    ui->DotPlotZone->setScene(&m_scene);

    BitString a = BitString::fromHex("AAF63E4");
    BitString b = BitString::fromHex("AAF63E4");
    this->setBitStrings(&a, &b);
    this->drawDiagonals();
    connect(this, SIGNAL(clicked()), this, SLOT(diagClicked(new DiagonalViewItem(5, 7, 15, 17,*m_classicPen))));

}

DotPlotView::~DotPlotView()
{
    delete ui;
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
    m_bitstring2 = b;
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

void DotPlotView::drawDiagonals() {
    qreal mw = ui->DotPlotZone->geometry().width() / m_width;
    qreal mh = ui->DotPlotZone->geometry().height() / m_height;

    for (std::list<Diagonal>::iterator it = m_listDiag.begin(); it != m_listDiag.end(); ++it){
        unsigned int x = (*it).getX();
        unsigned int y = (*it).getY();
        unsigned int l = (*it).length();
        DiagonalViewItem *diag = new DiagonalViewItem(x*mw, y*mh, (x+l)*mw, (y+l)*mh, *m_classicPen);
        m_scene.addItem(diag);
        //connect(diag, SIGNAL(diagonalClicked(DiagonalViewItem*)), this, SLOT(diagClicked(DiagonalViewItem*)));
        //m_scene.addLine(x*mw, y*mh, (x+l)*mw, (y+l)*mh, *m_classicPen);
        std::cout << "Diag " << (*it).toString() << std::endl ;

    }
    //debug
    /*std::cout << "<----------------------ListDiag--------------------------->" << std::endl;
        for (std::list<Diagonal>::iterator i = m_listDiag.begin(); i != m_listDiag.end(); i++ ){
        std::cout << "Diag " << (*i).toString() << std::endl ;
        }*/
}

void DotPlotView::setSelectedDiagonal(DiagonalViewItem *d) {
    if (d != NULL) {
        if (m_selectedDiagonal != NULL) {
            m_selectedDiagonal->setPen(*m_classicPen);
        }
        m_selectedDiagonal = d;
        m_selectedDiagonal->setPen(*m_selectedPen);
    }
}

void DotPlotView::refreshValues(qreal x, qreal y, qreal l) {
    ui->PosDump1Value->setText(QString((int) x));
    ui->PosDump2Value->setText(QString((int) y));
    ui->SizeDiagValue->setText(QString((int) l));
    ui->textZone->setText(QString(m_bitstring->substring(x, l).toString().c_str()));
}

void DotPlotView::diagClicked(DiagonalViewItem *d) {
    this->setSelectedDiagonal(d);
    this->refreshValues(d->line().x1(), d->line().y1(), d->line().dx());
}


/*void DotPlotView::mousePressEvent ( QMouseEvent * event ){
    if (event->buttons() == Qt::LeftButton) {
        int xm = event->localPos().x();
        int ym = event->localPos().y();
        if( xm >= ui->DotPlotZone->geometry().x() + 11
                && ym >= ui->DotPlotZone->geometry().y() + 11
                && xm <= ui->DotPlotZone->geometry().right()+1 + 11
                && ym <= ui->DotPlotZone->geometry().bottom()+1 + 11) {
            std::cout << xm << " " << ym << std::endl;
            std::cout << "touche" << ui->DotPlotZone->geometry().x() << " " << ui->DotPlotZone->geometry().y() << std::endl;

            QList<QGraphicsItem *> l = ui->DotPlotZone->items();
            QGraphicsLineItem *selectedDiagonal = static_cast<QGraphicsLineItem*>(l.first());
            //QGraphicsLineItem *selectedDiagonal = dynamic_cast<QGraphicsLineItem*>(m_scene.itemAt(ui->DotPlotZone->cursor().pos().x(), ui->DotPlotZone->cursor().pos().y(), QTransform()));
            if(selectedDiagonal != NULL){
                    if (m_selectedDiagonal != NULL) {
                        m_selectedDiagonal->setPen(*m_classicPen);
                    }
                    m_selectedDiagonal = selectedDiagonal;
                    m_selectedDiagonal->setPen(*m_selectedPen);
                    std::cout << m_selectedDiagonal->line().x1() << " " << m_selectedDiagonal->pos().y() << std::endl;
                    std::cout << "DEATH PENIS" << std::endl;

            }
        }
    }
}*/

