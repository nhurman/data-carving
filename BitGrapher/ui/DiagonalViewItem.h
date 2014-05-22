#ifndef DIAGONALVIEWITEM_H
#define DIAGONALVIEWITEM_H

#include <QWidget>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QPen>
#include <iostream>


class DiagonalViewItem : public QObject, public QGraphicsLineItem
{
    Q_OBJECT

public:
    DiagonalViewItem();
    DiagonalViewItem(qreal x1, qreal y1, qreal x2, qreal y2, QPen pen, QGraphicsItem * parent = 0);

protected:
    void mousePressEvent (QGraphicsSceneMouseEvent *event );


signals:
    void diagonalClicked(DiagonalViewItem *d);
};

#endif // DIAGONALVIEWITEM_H
