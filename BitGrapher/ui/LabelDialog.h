#ifndef LABELDIALOG_H
#define LABELDIALOG_H

#include <QDialog>
#include "core/Label.h"
#include "encoding/Encoding2.h"
#include <QMap>

namespace Ui {
class LabelDialog;
}

class LabelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LabelDialog(QWidget *parent = 0);
    ~LabelDialog();
    void setLabel(Label const& l);
    Label getLabel() const;
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
