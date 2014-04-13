#include "bitgrapharea.h"

BitGraphArea::BitGraphArea(QWidget *parent) :
    QWidget(parent)
{
}

void BitGraphArea::setBitString(BitString const* bs){
    m_bitstring = bs;
}



void BitGraphArea::paintEvent(QPaintEvent* /* event */){
    int width = this->width() - 2;
    int height = this->height() - 2;
    unsigned int lines = ceil(m_bitstring->size() / 64.);
    qreal w = width / 64, h = height / lines;
    qreal xoffset = 1 + (width % 64) / 2;
    qreal yoffset = 1 + (height % lines) / 2;

    QPainter painter(this);
    QLinearGradient gradientYes(0, 0, 0, h);
    gradientYes.setColorAt(0.0, QColor("#00baff"));
    gradientYes.setColorAt(1.0, QColor("#008ec3"));

    QLinearGradient gradientNo(0, 0, 0, h);
    gradientNo.setColorAt(0.0, QColor("#0075a0"));
    gradientNo.setColorAt(1.0, QColor("#004964"));

    for (unsigned int i = 0; i < lines; ++i) {
        for (unsigned int j = 0; j < 8 * 8 && i * 64 + j < m_bitstring->size(); ++j) {
            QLinearGradient* gradient = (*m_bitstring)[i*64+j] ? &gradientYes : &gradientNo;

            qreal x = xoffset + j * w;
            qreal y = yoffset + i * h;
            gradient->setStart(0, y);
            gradient->setFinalStop(0, y + h);

            painter.fillRect(x, y, w, h, *gradient);
        }
    }

    //*
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, this->width() - 1, this->height() - 1));
    //*/
}
