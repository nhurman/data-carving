#include "ViewWidget.h"


ViewWidget::ViewWidget(QWidget *parent) : QWidget(parent)
{
    m_pixmap = 0;
    m_bitString = 0;
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setBackgroundRole(QPalette::Light);
    if (parent) {
        parent->setBackgroundRole(QPalette::Light);
    }
}

ViewWidget::~ViewWidget()
{
    delete m_pixmap;
}

void ViewWidget::setBitString(BitString const* bs)
{
    m_bitString = bs;
    delete m_pixmap;
    m_pixmap = 0;
    update();
}

void ViewWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if (!m_pixmap) {
        generatePixmap();
        setMinimumSize(sizeHint());
    }

    QPainter painter(this);
    painter.drawPixmap(rect(), *m_pixmap);
}
