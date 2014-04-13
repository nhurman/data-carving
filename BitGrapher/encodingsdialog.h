#ifndef ENCODINGSDIALOG_H
#define ENCODINGSDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include "encoding.h"

namespace Ui {
class EncodingsDialog;
}

class EncodingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EncodingsDialog(QWidget *parent, QTextEdit* textEdit, BitString* bitString);
    ~EncodingsDialog();
    char (* getEncodingFunction())(char);
    void accept();

private:
    Ui::EncodingsDialog *ui;
    QTextEdit* m_textEdit;
    BitString* m_bitString;

};

#endif // ENCODINGSDIALOG_H
