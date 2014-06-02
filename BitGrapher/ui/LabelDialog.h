#ifndef LABELDIALOG_H
#define LABELDIALOG_H

#include <QDialog>
#include "core/Label.h"
#include "encoding/Encoding2.h"
#include <QMap>

namespace Ui {
class LabelDialog;
}

/*!
 * \class LabelDialog
 * \brief Label edition dialog
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
class LabelDialog : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief Constructor
     * \param parent Parent widget for garbage collection
     */
    explicit LabelDialog(QWidget *parent = 0);

    /*!
     * \brief Destructor
     */
    ~LabelDialog();

    /*!
     * \brief Set the label to display
     * \param l Label
     */
    void setLabel(Label const& l);

    /*!
     * \brief Get the displayed label
     * \return Label
     */
    Label getLabel() const;

    /*!
     * \brief Set the encodings list
     * \param encs Encodings
     */
    void setEncodings(QMap<QString, Encoding2*>* encs);

private slots:
    void on_index_valueChanged(int);
    void on_length_valueChanged(int);
    void on_encoding_currentIndexChanged(int);

private:
    Ui::LabelDialog *ui;
    QMap<QString, Encoding2*>* m_encodings;
    void updateValue();
};

#endif // LABELDIALOG_H
