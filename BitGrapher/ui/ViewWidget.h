#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QDebug>
#include <QPainter>

#include "core/BitString.h"

class ViewWidget : public QWidget
{
public:
    ViewWidget(QWidget *parent = 0);
    virtual ~ViewWidget();
    virtual QSize sizeHint() const = 0;

    virtual void setBitString(BitString const* bs);

protected:
    virtual void generatePixmap() = 0;

    void paintEvent(QPaintEvent* event);
    BitString const* m_bitString;
    QPixmap *m_pixmap;
};


#endif // VIEWWIDGET_H
