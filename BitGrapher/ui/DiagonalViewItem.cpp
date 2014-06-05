#include "DiagonalViewItem.h"

DiagonalViewItem::DiagonalViewItem() :
     QGraphicsLineItem()
{
}

DiagonalViewItem::DiagonalViewItem(unsigned int x, unsigned int y, unsigned int l, qreal mw, qreal mh, QPen pen, QGraphicsItem * parent) :
    QGraphicsLineItem(x*mw, y*mh, (x+l)*mw, (y+l)*mh, parent),
    m_x(x),
    m_y(y),
    m_l(l)
{
    this->setPen(pen);
    //this->setFlags(QGraphicsItem::ItemIsSelectable);
    this->setAcceptedMouseButtons(Qt::LeftButton);
}

unsigned int DiagonalViewItem::getX() {
    return m_x;
}

unsigned int DiagonalViewItem::getY(){
    return m_y;
}

unsigned int DiagonalViewItem::getL(){
    return m_l;
}


void DiagonalViewItem::mousePressEvent ( QGraphicsSceneMouseEvent * /*event*/ ){
    //std::cout << this->line().x1() << " " << this->line().y1() << " " << this->line().dx() << std::endl;
    emit diagonalClicked(this);
}
