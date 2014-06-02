#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QDebug>
#include <QPainter>

#include "core/BitString.h"

/*!
 * \class ViewWidget
 * \brief Base class for cached viewing widgets
 *
 * \author Nicolas Hurman
 * \date 02/03/2014
 */
class ViewWidget : public QWidget
{
public:
    /*!
     * \brief Constructor
     * \param parent Parent widget for garbage collection
     */
    ViewWidget(QWidget *parent = 0);

    /*!
     * \brief Destructor
     */
    virtual ~ViewWidget();

    /*!
     * \brief Gets the preferred size for this widget
     * \return Size
     */
    virtual QSize sizeHint() const = 0;

    /*!
     * \brief Sets the BitString to display
     * \param bs BitString to display
     */
    virtual void setBitString(BitString const* bs);

protected:
    /*!
     * \brief Draws the widget to the cached pixmap
     */
    virtual void generatePixmap() = 0;

    /*!
     * \brief Paint the widget to the screen
     * \param event Paint event
     */

    void paintEvent(QPaintEvent* event);
    BitString const* m_bitString;
    QPixmap *m_pixmap;
};


#endif // VIEWWIDGET_H
