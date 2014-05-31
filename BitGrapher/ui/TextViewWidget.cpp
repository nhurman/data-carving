#include "TextViewWidget.h"
#include "ui_TextViewWidget.h"

#include <QDebug>
#include "encoding/BCD.h"
#include "encoding/ASCII7.h"
#include "encoding/ASCII8.h"
#include "encoding/Binary.h"
#include "encoding/Integer.h"

TextViewWidget::TextViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextViewWidget)
{
    ui->setupUi(this);
    m_bitString = 0;
    m_encodings = 0;
    m_encoding = 0;
    m_globalOffset = 0;
}

TextViewWidget::~TextViewWidget()
{
    delete ui;
}

void TextViewWidget::setEncodings(QMap<QString, Encoding2*>* encodings)
{
    m_encodings = encodings;
    m_encoding = (*m_encodings)["ASCII (8 bits)"];
}

void TextViewWidget::setBitString(BitString const* bs)
{
    m_bitString = bs;
    updateContents();
}

void TextViewWidget::updateContents()
{
    ui->textEdit->clear();
    m_encoding->setBitString(m_bitString);
    m_encoding->setGlobalOffset(m_globalOffset);

    QString contents;
    for (unsigned int i = 0; i < m_encoding->countChunks(); ++i) {
        contents += m_encoding->getChunk(i).c_str();
    }

    ui->textEdit->setText(contents);
}

void TextViewWidget::on_encoding_currentIndexChanged(const QString &arg1)
{
    m_encoding = (*m_encodings)[arg1];
    updateContents();
}

void TextViewWidget::on_globalOffset_valueChanged(int arg1)
{
    m_globalOffset = arg1;
    updateContents();
}

void TextViewWidget::on_newLabel_clicked()
{
    if (!m_encoding || !m_bitString) return;

    unsigned int outSize = m_encoding->getChunk(0).size();
    QTextCursor cursor = ui->textEdit->textCursor();
    unsigned int start = m_encoding->bitsPerChunk() * (cursor.selectionStart() / outSize);
    unsigned int end = m_encoding->bitsPerChunk() * ceil(static_cast<double>(cursor.selectionEnd()) / outSize);

    Label l;
    l.name = ui->lineEdit->text().toUtf8().constData();
    l.index = start + m_globalOffset;
    l.length = end - start;
    l.encoding = m_encoding->getName();
    //l.value = m_encoding->decode(l.index, l.length);

    emit labelAdded(l);
    ui->lineEdit->clear();
    ui->textEdit->setFocus(Qt::OtherFocusReason);
}
