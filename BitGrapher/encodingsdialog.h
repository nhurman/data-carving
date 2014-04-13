#ifndef ENCODINGSDIALOG_H
#define ENCODINGSDIALOG_H

#include <QDialog>

namespace Ui {
class EncodingsDialog;
}

class EncodingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EncodingsDialog(QWidget *parent = 0);
    ~EncodingsDialog();

private:
    Ui::EncodingsDialog *ui;
};

#endif // ENCODINGSDIALOG_H
