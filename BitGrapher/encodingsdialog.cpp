#include "encodingsdialog.h"
#include "ui_encodingsdialog.h"

EncodingsDialog::EncodingsDialog(QWidget *parent, QTextEdit *textEdit, BitString* bitString, Encoding* encoding) :
    QDialog(parent),
    ui(new Ui::EncodingsDialog),
    m_textEdit(textEdit),
    m_bitString(bitString),
    m_encoding(encoding)
{
    ui->setupUi(this);
    int index = ui->encoding->findText(encoding->getName());
    if(index != -1) { // -1 for not found
        ui->encoding->setCurrentIndex(index);
    }
    ui->globalOffset->setValue(encoding->getGlobalOffset());
    ui->localOffset->setValue(encoding->getLocalOffset());
    ui->charSize->setValue(encoding->getCharSize());

    QObject::connect(ui->encoding, SIGNAL(currentIndexChanged( QString ) ),
                          this, SLOT(onComboBoxChange( QString )));
}

EncodingsDialog::~EncodingsDialog()
{
    delete ui;
}

void EncodingsDialog::accept()
{
    *m_encoding = Encoding(ui->encoding->currentText(), ui->globalOffset->value(), ui->localOffset->value(), ui->charSize->value());

    QDialog::accept();
}

void EncodingsDialog::onComboBoxChange(QString str)
{
    int value;
    if(str == "Binary")
        value = 1;
    else if(str == "Hexadecimal")
        value = 4;
    else
        value = 7;
    ui->charSize->setMinimum(value);
    ui->charSize->setValue(value);
}
