#ifndef HEXVIEWWIDGET_H
#define HEXVIEWWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPainter>
#include <QDebug>
#include <QTextDocument>

#include "core/BitString.h"
#include "encoding/Encoding.h"
#include "encoding/Hexadecimal.h"
#include "encoding/ASCII.h"

class HexViewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HexViewWidget(QWidget *parent = 0);
    ~HexViewWidget();
    void setBitString(BitString const* bs);
    QSize sizeHint() const;

signals:

public slots:

protected:
    void paintEvent(QPaintEvent* /* event */);

    BitString const* m_bitString;
    Encoding* m_decoder;

};

#endif // HEXVIEWWIDGET_H
