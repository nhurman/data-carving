#include "encodingsdialog.h"
#include "ui_encodingsdialog.h"

EncodingsDialog::EncodingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EncodingsDialog)
{
    ui->setupUi(this);
}

EncodingsDialog::~EncodingsDialog()
{
    delete ui;
}
