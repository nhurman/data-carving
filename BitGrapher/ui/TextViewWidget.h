#ifndef TEXTVIEWWIDGET_H
#define TEXTVIEWWIDGET_H

#include <QWidget>
#include <QMap>
#include "core/BitString.h"
#include "core/Label.h"
#include "encoding/Encoding2.h"

namespace Ui {
class TextViewWidget;
}

/*!
 * \class TextViewWidget
 * \brief Text viewing widget
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
class TextViewWidget : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor
     * \param parent Parent widget for garbage collection
     */
    explicit TextViewWidget(QWidget *parent = 0);

    /*!
     * \brief Destructor
     */
    ~TextViewWidget();

    /*!
     * \brief Set the BitString to display
     * \param bs BitString
     */
    void setBitString(BitString const* bs);

    /*!
     * \brief Set the encodings list
     * \param encodings Encodings
     */
    void setEncodings(QMap<QString, Encoding2*>* encodings);

signals:
    /*!
     * \brief Fired when a label is added
     * \param l Label
     */
    void labelAdded(Label l);

private slots:
    void on_encoding_currentIndexChanged(const QString &arg1);
    void on_globalOffset_valueChanged(int arg1);
    void on_newLabel_clicked();

private:
    void updateContents();
    Ui::TextViewWidget *ui;
    BitString const* m_bitString;
    Encoding2 *m_encoding;
    QMap<QString, Encoding2*>* m_encodings;
    unsigned int m_globalOffset;
};

#endif // TEXTVIEWWIDGET_H
