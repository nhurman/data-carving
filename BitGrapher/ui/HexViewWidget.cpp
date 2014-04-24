#include "HexViewWidget.h"
#include "encoding/Hexadecimal.h"
#include "encoding/ASCII.h"

#include <QPainter>
#include <QDebug>
#include <QTextDocument>

HexViewWidget::HexViewWidget(QWidget *parent) :
    QWidget(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_decoder = new Hexadecimal();
}

HexViewWidget::~HexViewWidget()
{
    delete m_decoder;
}

void HexViewWidget::setBitString(BitString const* bs)
{
    m_decoder->setBitString(bs);
}

QSize HexViewWidget::sizeHint() const
{
    int w = m_decoder->LineWidth();
    int h = m_decoder->LineHeight() * m_decoder->lines();

    return QSize(w + 150, h + 2);
}

void HexViewWidget::paintEvent(QPaintEvent* /* event */)
{
    QPainter painter(this);

    if (!m_decoder->bitString()) {
        return;
    }

    setBackgroundRole(QPalette::Light);

    QTextDocument doc;
    doc.setHtml(QString("<pre>") + m_decoder->toHTML().c_str() + "</pre>");
    doc.drawContents(&painter, rect());


    painter.drawLine(
        QPoint(m_decoder->LineWidth() + 6, 0),
        QPoint(m_decoder->LineWidth() + 6, m_decoder->lines() * m_decoder->LineHeight() + 2));

    Encoding *decoder2 = new ASCII(m_decoder->bitString());
    doc.setHtml(QString("<pre>") + decoder2->toHTML().c_str() + "</pre>");
    painter.translate(m_decoder->LineWidth() + 6, 0);
    doc.drawContents(&painter, rect());
    delete decoder2;
}
