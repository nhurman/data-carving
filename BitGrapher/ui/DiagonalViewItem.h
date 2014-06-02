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
    /// \param x X position of the upper left point.
    /// \param y Y position of the upper left point.
    /// \param l Length of the diagonal in bit.
    /// \param mw X scaling.
    /// \param mw Y scaling.
    /// \param pen Pen used to draw the line.
    /// \param parent The parent Widget (optional).
    DiagonalViewItem(unsigned int x, unsigned int y, unsigned int l, qreal mw, qreal mh, QPen pen, QGraphicsItem * parent = 0);

    /// \brief X Accessor.
    /// \return Value of m_x.
    unsigned int getX();

    /// \brief Y Accessor.
    /// \return Value of m_y.
    unsigned int getY();

    /// \brief Length Accessor.
    /// \return Value of m_l.
    unsigned int getL();


protected:
    /// \brief Method called when you click on a diagonal.
    /// \param event Countain informations about the click.
    void mousePressEvent (QGraphicsSceneMouseEvent *event );


signals:
    /// \brief Tell the window that a diagonal was clicked.
    /// \param d Diagonal that sent the signal.
    void diagonalClicked(DiagonalViewItem *d);

private:
    unsigned int m_x; ///< Diagonal position on X axis (in dump)
    unsigned int m_y; ///< Diagonal position on Y axis (in dump)
    unsigned int m_l; ///< Diagonal length (in bit)
};

#endif // DIAGONALVIEWITEM_H
