#ifndef DOTPLOTVIEW_H
#define DOTPLOTVIEW_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QString>
#include <iostream>
#include "core/bitstring.h"

class DotPlotView : public QWidget
{
    Q_OBJECT
public:
    explicit DotPlotView(QWidget *parent = 0);
    void setDiagonals(std::list<Diagonal> const sd, unsigned int w, unsigned int h);
    void setDiagonals(std::list<Diagonal> const sd);
    void setBitString(const BitString *b);
    void setBitStrings(BitString const* b1, BitString const* b2);


signals:

public slots:

protected:
    void paintEvent(QPaintEvent* /* event */);

    std::list<Diagonal> m_listDiag;
    BitString const* m_bitstring;
    BitString const* m_bitstring2;
    unsigned int m_height;
    unsigned int m_width;
};

#endif // DOTPLOTVIEW_H
