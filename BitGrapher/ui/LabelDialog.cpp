#include "LabelDialog.h"
#include "ui_LabelDialog.h"

LabelDialog::LabelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LabelDialog)
{
    ui->setupUi(this);
    m_encodings = 0;
}

LabelDialog::~LabelDialog()
{
    delete ui;
}

void LabelDialog::setEncodings(QMap<QString, Encoding2*>* encs)
{
    m_encodings = encs;
}

void LabelDialog::setLabel(Label const& l)
{
    ui->name->setText(l.name.c_str());
    ui->index->setValue(l.index);
    ui->length->setValue(l.length);
    ui->encoding->setCurrentText(l.encoding.c_str());
}

Label LabelDialog::getLabel() const
{
    Label l;
    l.name = ui->name->text().toUtf8().constData();
    l.index = ui->index->value();
    l.length = ui->length->value();
    l.encoding = ui->encoding->currentText().toUtf8().constData();
    return l;
}

void LabelDialog::on_index_valueChanged(int)
{
    updateValue();
}

void LabelDialog::on_length_valueChanged(int)
{
    updateValue();
}

void LabelDialog::on_encoding_currentIndexChanged(int)
{
    updateValue();
}

void LabelDialog::updateValue()
{
    Encoding2* e = (*m_encodings)[ui->encoding->currentText()];
    QString value = e->decode(ui->index->value(), ui->length->value()).c_str();
    ui->value->setText(value);
}
