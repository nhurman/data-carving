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
    /// \param listDiag List of Diagonal to be converted in DiagonalViewItem.
    void drawDiagonals(std::list<Diagonal> *listDiag);

    /// \brief Set the diagonal that will be drawed.
    void setSelectedDiagonal(DiagonalViewItem *d);

    /// \brief Refresh the numerical values of the interface.
    /// \param x Position in the first dump.
    /// \param y Position in the second dump.
    /// \param l Length of the current diagonal.
    void refreshValues(qreal x, qreal y, qreal l);

    /// \brief Set the window title when only one dump is used.
    /// \param name1 Name of the dump used.
    void setWindowTitle(QString name1);

    /// \brief Set the window title when two dumps are used.
    /// \param name1 Name of the first dump used.
    /// \param name1 Name of the second dump used.
    void setWindowTitle(QString name1, QString name2);

signals:

public slots:

    /// \brief Slot that refresh all the interface on diagonal click.
    /// \param d The clicked diagonal.
    void diagClicked(DiagonalViewItem *d);

private:
    Ui::DotPlotView *ui; ///< The interface.
    QGraphicsScene m_scene; ///< The scene that should be drawed.
    BitString const* m_bitstring; ///< First bitstring.
    BitString const* m_bitstring2; ///< Second bitstring.
    unsigned int m_height; ///< Height of the graphical view.
    unsigned int m_width; ///< Width of the graphical view.
    QPen *m_classicPen; ///< Pen used for all unselected diagonals.
    QPen *m_selectedPen; ///< Pen used for the selected diagonal.
    QGraphicsLineItem *m_selectedDiagonal; ///< Adress of the selected diagonal.

};

#endif // DOTPLOTVIEW_H
