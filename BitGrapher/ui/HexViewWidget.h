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
#include "ViewWidget.h"

/*!
 * \class HexViewWidget
 * \brief Hexadecimal view widget
 *
 * \author Nicolas Hurman
 * \date 02/03/2014
 */
class HexViewWidget : public ViewWidget
{
    Q_OBJECT

public:
    explicit HexViewWidget(QWidget *parent = 0);
    ~HexViewWidget();
    QSize sizeHint() const;
    void setBitString(BitString const* bs);

signals:

public slots:

protected:
    void generatePixmap();

    BitString const* m_bitString;
    Encoding* m_decoder;
    Encoding* m_decoder2;

};

#endif // HEXVIEWWIDGET_H
