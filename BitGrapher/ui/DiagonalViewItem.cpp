#include "DiagonalViewItem.h"

DiagonalViewItem::DiagonalViewItem() :
     QGraphicsLineItem()
{
}

DiagonalViewItem::DiagonalViewItem(qreal x1, qreal y1, qreal x2, qreal y2, QPen pen, QGraphicsItem * parent) :
    QGraphicsLineItem(x1, y1, x2, y2, parent)
{
    this->setPen(pen);
    //this->setFlags(QGraphicsItem::ItemIsSelectable);
    this->setAcceptedMouseButtons(Qt::LeftButton);
}


void DiagonalViewItem::mousePressEvent ( QGraphicsSceneMouseEvent * event ){
    //std::cout << this->line().x1() << " " << this->line().y1() << " " << this->line().dx() << std::endl;
    emit diagonalClicked(this);
}
