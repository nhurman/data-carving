#include "DotPlotView.h"

DotPlotView::DotPlotView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DotPlotView),
    m_classicPen(new QPen(Qt::blue)),
    m_selectedPen(new QPen(Qt::red)),
    m_selectedDiagonal(new DiagonalViewItem())
{
    ui->setupUi(this);

    /*BitString a = BitString::fromHex("AAF63E4");
    BitString b = BitString::fromHex("AAF63E4");
    this->setBitStrings(&a, &b);*/
}

DotPlotView::~DotPlotView()
{
    delete ui;
}

void DotPlotView::setBitString(BitString const* b, unsigned int diagSize){
    m_bitstring = b;
    m_bitstring2 = b;
    m_height = b->size();
    m_width = b->size();
    std::list<Diagonal> d = b->dotPlotPattern(diagSize);
    drawDiagonals(&d);
}

void DotPlotView::setBitStrings(BitString const* b1, BitString const* b2, unsigned int diagSize){
    m_bitstring = b1;
    m_bitstring2 = b2;
    m_height = b2->size();
    m_width = b1->size();
    std::list<Diagonal> d = b1->dotPlotPattern(b2, diagSize);
    drawDiagonals(&d);
}

void DotPlotView::drawDiagonals(std::list<Diagonal>  *listDiag) {
    qreal mw = ui->DotPlotZone->geometry().width() / m_width;
    qreal mh = ui->DotPlotZone->geometry().height() / m_height;

    QGraphicsScene *scene = new QGraphicsScene();
    for (std::list<Diagonal>::iterator it = listDiag->begin(); it != listDiag->end(); ++it){
        unsigned int x = (*it).getX();
        unsigned int y = (*it).getY();
        unsigned int l = (*it).length();
        DiagonalViewItem *diag = new DiagonalViewItem(x*mw, y*mh, (x+l)*mw, (y+l)*mh, *m_classicPen);
        scene->addItem(diag);
        connect(diag, SIGNAL(diagonalClicked(DiagonalViewItem*)), this, SLOT(diagClicked(DiagonalViewItem*)));
        std::cout << "Diag " << (*it).toString() << std::endl ;

    }
    ui->DotPlotZone->setScene(scene);
}


void DotPlotView::setSelectedDiagonal(DiagonalViewItem *d) {
    if (d != NULL) {
        m_selectedDiagonal->setPen(*m_classicPen);
        m_selectedDiagonal = d;
        m_selectedDiagonal->setPen(*m_selectedPen);
    }
}

void DotPlotView::refreshValues(qreal x, qreal y, qreal l) {
    //std::cout << x << " " << y << " " << l << std::endl;
    ui->PosDump1Value->setText(QString::number(x));
    ui->PosDump2Value->setText(QString::number(y));
    ui->SizeDiagValue->setText(QString::number(l));
    ui->textZone->setText(QString(m_bitstring->substring(x, l).toString().c_str()));
}

void DotPlotView::diagClicked(DiagonalViewItem *d) {
    if (d != NULL) {
        this->setSelectedDiagonal(d);
        this->refreshValues(d->line().x1(), d->line().y1(), d->line().dx());
    }
}

void DotPlotView::setWindowTitle(QString name1) {
    QWidget::setWindowTitle("Dot Plot Pattern of " + name1);
}
void DotPlotView::setWindowTitle(QString name1, QString name2) {
    QWidget::setWindowTitle("Dot Plot Pattern between " + name1 + " and " + name2);
}
