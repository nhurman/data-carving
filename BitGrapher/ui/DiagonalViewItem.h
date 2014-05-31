#ifndef DIAGONALVIEWITEM_H
#define DIAGONALVIEWITEM_H

#include <QWidget>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QPen>
#include <iostream>

/// \class DiagonalViewItem
///
/// \brief Objects reprensenting diagonal in the graphical view
///
/// \author Gaugry Thierry
///
/// \date 24/05/2014


class DiagonalViewItem : public QObject, public QGraphicsLineItem
{
    Q_OBJECT

public:

    /// \brief Constructor for DiagonalViewItem.
    /// \note Default constructor, should not be used.
    DiagonalViewItem();

    /// \brief Constructor for DiagonalViewItem.
    /// \param x1 X position of the upper left point.
    /// \param y1 Y position of the upper left point.
    /// \param x2 X position of the bottom right point.
    /// \param y2 Y position of the bottom right point.
    /// \param pen Pen used to draw the line.
    /// \param parent The parent Widget (optional).
    DiagonalViewItem(qreal x1, qreal y1, qreal x2, qreal y2, QPen pen, QGraphicsItem * parent = 0);

protected:
    /// \brief Method called when you click on a diagonal.
    /// \param event Countain informations about the click.
    void mousePressEvent (QGraphicsSceneMouseEvent *event );


signals:
    /// \brief Tell the window that a diagonal was clicked.
    /// \param d Diagonal that sent the signal.
    void diagonalClicked(DiagonalViewItem *d);
};

#endif // DIAGONALVIEWITEM_H
