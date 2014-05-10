#ifndef DOTPLOTVIEW_H
#define DOTPLOTVIEW_H

#include <QWidget>

#include "ui_DotPlotView.h"

#include "algorithms/Diagonal.h"
#include "core/bitstring.h"

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

signals:

public slots:

protected:
    //void paintEvent(QPaintEvent* /* event */);

private:
    Ui::DotPlotView *ui;
    std::list<Diagonal> m_listDiag;
    BitString const* m_bitstring;
    BitString const* m_bitstring2;
    unsigned int m_height;
    unsigned int m_width;

};

#endif // DOTPLOTVIEW_H
