#include "encodingsdialog.h"
#include "ui_encodingsdialog.h"

EncodingsDialog::EncodingsDialog(QWidget *parent, QTextEdit *textEdit, BitString* bitString) :
    QDialog(parent),
    ui(new Ui::EncodingsDialog),
    m_textEdit(textEdit),
    m_bitString(bitString)
{
    ui->setupUi(this);
}

EncodingsDialog::~EncodingsDialog()
{
    delete ui;
}

char (* EncodingsDialog::getEncodingFunction())(char)
{
    QString item = ui->encoding->currentText();
    if(item == "Binary")
        return Encoding::toASCII;
    else
        return Encoding::toHexadecimal;
}

void EncodingsDialog::accept()
{
    QString content = m_textEdit->toPlainText();
    content = QString::fromStdString(
                Encoding::encode(*m_bitString, Encoding::toHexadecimal, ui->globalOffset->value(), ui->localOffset->value(), 4));
    std::cout << "Encode " << content.toStdString() << std::endl;
    m_textEdit->setPlainText(content);
    QDialog::accept();
}
