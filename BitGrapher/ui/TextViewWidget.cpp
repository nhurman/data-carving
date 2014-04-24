#include "TextViewWidget.h"
#include "encoding/Hexadecimal.h"
#include <QPainter>
#include <QDebug>

TextViewWidget::TextViewWidget(QWidget *parent) : ViewWidget(parent)
{
    m_decoder = new Hexadecimal();
    m_bitString = 0;
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setMinimumSize(sizeHint());
    m_bytesPerLine = 10;
}

TextViewWidget::~TextViewWidget()
{
    delete m_decoder;
}

QSize TextViewWidget::sizeHint() const
{
    if (!m_bitString) {
        return QSize(1, 1);
    }

    unsigned int charWidth = 16, charHeight = 16;
    unsigned int width = m_bytesPerLine * charWidth;
    unsigned int lines = ceil(m_bitString->size() / (m_bytesPerLine * 8.));
    unsigned int height = lines * charHeight;

    qDebug() << width << height;

    // width = charactersToDisplay * characterWidth
    // charsToDisplay



    return QSize(width, height);
}

void TextViewWidget::generatePixmap()
{
    qDebug() << "Generating pixmap";
    m_decoder->setBitString(m_bitString);
    //m_decoder->

    /*if (!m_bitString) {
        return;
    }*/

    m_pixmap = new QPixmap(sizeHint());
    m_pixmap->fill(Qt::white);

    QPainter painter(m_pixmap);
    painter.drawText(QPoint(0, 0), "Hellow");
    painter.drawLine(QPoint(0, 0), QPoint(100, 100));
}
