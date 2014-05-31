#include "HexViewWidget.h"


HexViewWidget::HexViewWidget(QWidget *parent) :
    ViewWidget(parent)
{
    m_decoder = new Hexadecimal();
    m_decoder2 = new ASCII();
}

HexViewWidget::~HexViewWidget()
{
    delete m_decoder;
    delete m_decoder2;
}

QSize HexViewWidget::sizeHint() const
{
    int w = m_decoder->LineWidth() + m_decoder2->LineWidth();
    int h = m_decoder->LineHeight() * m_decoder->lines();

    return QSize(w + 6, h + 4);
}

void HexViewWidget::setBitString(BitString const* bs)
{
    ViewWidget::setBitString(bs);
    m_decoder->setBitString(bs);
    m_decoder2->setBitString(bs);
}

void HexViewWidget::generatePixmap()
{
    m_pixmap = new QPixmap(sizeHint());
    m_pixmap->fill(Qt::white);

    QPainter painter(m_pixmap);

    if (!m_decoder->bitString()) {
        return;
    }

    QTextDocument doc;
    doc.setHtml(QString("<pre>") + m_decoder->toHTML().c_str() + "</pre>");
    doc.drawContents(&painter, QRect(0, 0, m_pixmap->width(), m_pixmap->height()));

    painter.drawLine(
        QPoint(m_decoder->LineWidth() + 4, 0),
        QPoint(m_decoder->LineWidth() + 4, m_decoder->lines() * m_decoder->LineHeight() + 2));

    doc.setHtml(QString("<pre>") + m_decoder2->toHTML().c_str() + "</pre>");
    painter.translate(m_decoder->LineWidth() + 6, 0);
    doc.drawContents(&painter, QRect(0, 0, m_pixmap->width(), m_pixmap->height()));
}
