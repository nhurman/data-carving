#ifndef BITMAPWIDGET_H
#define BITMAPWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDebug>

#include "ViewWidget.h"

/*!
 * \class BitmapWidget
 * \brief Bitmap view widget
 *
 * \author Nicolas Hurman
 * \date 02/03/2014
 */
class BitmapWidget : public ViewWidget
{
public:
    BitmapWidget(QWidget *parent = 0);
    ~BitmapWidget();
    QSize sizeHint() const;

    static const unsigned int BitsPerLine = 64;
    static const unsigned int SquareSize = 10;


protected:
    void generatePixmap();

};

#endif // BITMAPWIDGET_H
