#ifndef BITGRAPHAREA_H
#define BITGRAPHAREA_H

#include <QWidget>
#include <QPainter>
#include "core/bitstring.h"

class BitGraphArea : public QWidget
{
    Q_OBJECT
public:
    explicit BitGraphArea(QWidget *parent = 0);
    void setBitString(BitString const* bs);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent* /* event */);

    BitString const* m_bitstring;

};

#endif // BITGRAPHAREA_H
