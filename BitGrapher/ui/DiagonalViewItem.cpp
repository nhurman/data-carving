#include "DiagonalViewItem.h"

DiagonalViewItem::DiagonalViewItem()
{
}

DiagonalViewItem::DiagonalViewItem(qreal x1, qreal y1, qreal x2, qreal y2, QPen pen, QGraphicsItem * parent) :
    QGraphicsLineItem(x1, y1, x2, y2, parent)
{
    this->setPen(pen);
}


void DiagonalViewItem::mousePressEvent ( QMouseEvent * event ){
    if (event->buttons() == Qt::LeftButton) {
        std::cout << this->line().x1() << " " << this->line().y1() << " " << this->line().dx() << std::endl;
        emit diagonalClicked(this);
    }
}
