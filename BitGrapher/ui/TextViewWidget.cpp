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
    m_encoding = new ASCII8();
}

TextViewWidget::~TextViewWidget()
{
    delete ui;
    delete m_encoding;
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
    if ("BCD (6 bits)" == arg1) {
        delete m_encoding;
        m_encoding = new BCD();
    }
    else if ("ASCII (7 bits)" == arg1) {
        delete m_encoding;
        m_encoding = new ASCII7();
    }
    else if ("ASCII (8 bits)" == arg1) {
        delete m_encoding;
        m_encoding = new ASCII8();
    }
    else if ("Binary" == arg1) {
        delete m_encoding;
        m_encoding = new Binary();
    }
    else if ("Integer (2 bits)" == arg1) {
        delete m_encoding;
        m_encoding = new Integer2();
    }
    else if ("Integer (3 bits)" == arg1) {
        delete m_encoding;
        m_encoding = new Integer3();
    }
    else if ("Integer (4 bits)" == arg1) {
        delete m_encoding;
        m_encoding = new Integer4();
    }
    else if ("Integer (5 bits)" == arg1) {
        delete m_encoding;
        m_encoding = new Integer5();
    }
    else if ("Integer (6 bits)" == arg1) {
        delete m_encoding;
        m_encoding = new Integer6();
    }
    else if ("Integer (7 bits)" == arg1) {
        delete m_encoding;
        m_encoding = new Integer7();
    }
    else if ("Integer (8 bits)" == arg1) {
        delete m_encoding;
        m_encoding = new Integer8();
    }
    else if ("Integer (16 bits)" == arg1) {
        delete m_encoding;
        m_encoding = new Integer16();
    }
    else if ("Integer (32 bits)" == arg1) {
        delete m_encoding;
        m_encoding = new Integer32();
    }

    updateContents();
}

void TextViewWidget::on_globalOffset_valueChanged(int arg1)
{
    m_globalOffset = arg1;
    updateContents();
}

void TextViewWidget::on_newLabel_clicked()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    qDebug() << cursor.selectionStart() << cursor.selectionEnd();
}
