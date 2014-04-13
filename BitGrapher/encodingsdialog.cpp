#include "encodingsdialog.h"
#include "ui_encodingsdialog.h"

EncodingsDialog::EncodingsDialog(QWidget *parent, QTextEdit *textEdit, BitString* bitString, int *charSize) :
    QDialog(parent),
    ui(new Ui::EncodingsDialog),
    m_textEdit(textEdit),
    m_bitString(bitString),
    m_charSize(charSize)
{
    ui->setupUi(this);
    QObject::connect(ui->encoding, SIGNAL(currentIndexChanged( QString ) ),
                          this, SLOT(onComboBoxChange( QString )));
}

EncodingsDialog::~EncodingsDialog()
{
    delete ui;
}

char (* EncodingsDialog::getEncodingFunction())(char)
{
    QString item = ui->encoding->currentText();
    if(item == "Hexadecimal")
        return Encoding::reverseHexadecimal;
    else
        return Encoding::toASCII;
}

void EncodingsDialog::accept()
{
    QString content;
    if(ui->encoding->currentText() == "Binary") {
        content = QString::fromStdString(m_bitString->toString());
    }
    else {
    content = QString::fromStdString(
                Encoding::encode(*m_bitString, getEncodingFunction(), ui->globalOffset->value(), ui->localOffset->value(), ui->charSize->value()));
    }
    m_textEdit->setPlainText(content);
    *m_charSize = ui->charSize->value();
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
