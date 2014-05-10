#ifndef TEXTVIEWWIDGET_H
#define TEXTVIEWWIDGET_H

#include <QPainter>
#include <QDebug>
#include <QPixmapCache>

#include "ViewWidget.h"
#include "encoding/Encoding.h"
#include "encoding/Hexadecimal.h"

class TextViewWidget : public ViewWidget
{
public:
    TextViewWidget(QWidget *parent = 0);
    ~TextViewWidget();
    QSize sizeHint() const;

protected:
    Encoding *m_decoder;
    unsigned int m_bytesPerLine;
    void generatePixmap();
};


#endif // TEXTVIEWWIDGET_H
