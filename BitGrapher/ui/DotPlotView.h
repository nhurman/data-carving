#ifndef DOTPLOTVIEW_H
#define DOTPLOTVIEW_H

#include <QWidget>
#include <QPen>
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QScrollArea>
#include <QGraphicsLineItem>
#include <QTextEdit>
#include <QMouseEvent>


#include "ui_DotPlotView.h"

#include "algorithms/Diagonal.h"
#include "core/BitString.h"

#include "DiagonalViewItem.h"


/// \class DotPlotView
///
/// \brief Window that show result of Dot Plot Pattern Algorithm.
///
/// \author Gaugry Thierry
///
/// \date 24/05/2014

namespace Ui {
class DotPlotView;
}

class DotPlotView : public QWidget
{
    Q_OBJECT

public:

    /// \brief Constructor for DotPlotView window.
    /// \param parent The parent Widget (optional).
    explicit DotPlotView(QWidget *parent = 0);

    /// \brief Destructor for AssociationViewWidget.
    ~DotPlotView();

    /// \brief Set diagonals on the graphic view.
    /// \param sd List of diagonal to add.
    /// \param w Graphic view width.
    /// \param h Graphic view height.
    void setDiagonals(std::list<Diagonal> const sd, unsigned int w, unsigned int h);

    /// \brief Set diagonals on the graphic view.
    /// \param sd List of diagonal to add.
    void setDiagonals(std::list<Diagonal> const sd);

    /// \brief Set bitstring.
    /// \param b BitString used on axis X and Y.
    /// \note Also set diagonals with the given bitstring.
    void setBitString(BitString const* b);

    /// \brief Set bitstrings.
    /// \param b1 BitString used on axis X.
    /// \param b2 BitString used on axis Y.
    /// \note Also set diagonals with the given bitstrings.
    void setBitStrings(BitString const* b1, BitString const* b2);

    /// \brief Draw diagonals on the graphic view.
    void drawDiagonals();

    void setSelectedDiagonal(DiagonalViewItem *d);
    void refreshValues(qreal x, qreal y, qreal l);

signals:

public slots:
    void diagClicked(DiagonalViewItem *d);

private:
    Ui::DotPlotView *ui;
    QGraphicsScene m_scene;
    std::list<Diagonal> m_listDiag;
    BitString const* m_bitstring;
    BitString const* m_bitstring2;
    unsigned int m_height;
    unsigned int m_width;
    QPen *m_classicPen;
    QPen *m_selectedPen;
    QGraphicsLineItem *m_selectedDiagonal;

};

#endif // DOTPLOTVIEW_H
