#include "BitmapWidget.h"

#include <QDebug>

BitmapWidget::BitmapWidget(QWidget *parent) :
    ViewWidget(parent)
{

}

BitmapWidget::~BitmapWidget()
{

}


QSize BitmapWidget::sizeHint() const
{
    if (NULL == m_bitString) {
        return QSize(1, 1);
    }

    return QSize(BitsPerLine * SquareSize, //700);
        SquareSize * ceil(m_bitString->size() / static_cast<float>(BitsPerLine)));
}

void BitmapWidget::generatePixmap()
{
    m_pixmap = new QPixmap(sizeHint());
    m_pixmap->fill(Qt::white);
    QPainter painter(m_pixmap);

    if (NULL != m_bitString) {
        unsigned int lines = ceil(m_bitString->size() / static_cast<float>(BitsPerLine));
        qreal w = SquareSize, h = SquareSize;

        QLinearGradient gradientYes(0, 0, 0, h);
        gradientYes.setColorAt(0.0, QColor("#00baff"));
        gradientYes.setColorAt(1.0, QColor("#008ec3"));

        QLinearGradient gradientNo(0, 0, 0, h);
        gradientNo.setColorAt(0.0, QColor("#0075a0"));
        gradientNo.setColorAt(1.0, QColor("#004964"));

        for (unsigned int i = 0; i < lines; ++i) {
            for (unsigned int j = 0; j < BitsPerLine && i * BitsPerLine + j < m_bitString->size(); ++j) {
                QLinearGradient* gradient = (*m_bitString)[i*BitsPerLine+j] ? &gradientYes : &gradientNo;

                qreal x = j * w;
                qreal y = i * h;
                gradient->setStart(0, y);
                gradient->setFinalStop(0, y + h);

                painter.fillRect(x, y, w, h, *gradient);
            }
        }
    }

    /*
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, this->width() - 1, this->height() - 1));
    //*/
}
