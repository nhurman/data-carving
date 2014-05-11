#ifndef DOTPLOTVIEW_H
#define DOTPLOTVIEW_H

#include <QWidget>
#include <QPen>
#include <Qpainter>
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
//class DiagonalViewItem;



namespace Ui {
class DotPlotView;
}

class DotPlotView : public QWidget
{
    Q_OBJECT

public:
    explicit DotPlotView(QWidget *parent = 0);
    ~DotPlotView();
    void setDiagonals(std::list<Diagonal> const sd, unsigned int w, unsigned int h);
    void setDiagonals(std::list<Diagonal> const sd);
    void setBitString(BitString const* b);
    void setBitStrings(BitString const* b1, BitString const* b2);
    void drawDiagonals();

    void setSelectedDiagonal(DiagonalViewItem *d);
    void refreshValues(qreal x, qreal y, qreal l);




signals:

public slots:
    void diagClicked(DiagonalViewItem *d);


protected:
    //void mousePressEvent ( QMouseEvent * event );


private:
    Ui::DotPlotView *ui;
    QGraphicsScene m_scene;
    std::list<Diagonal> m_listDiag;
    BitString const* m_bitstring;
    BitString const* m_bitstring2;
    unsigned int m_height;
    unsigned int m_width;
    //QGraphicsItem *m_selectedDiagonal;
    QPen *m_classicPen;
    QPen *m_selectedPen;
    QGraphicsLineItem *m_selectedDiagonal;

};

#endif // DOTPLOTVIEW_H
