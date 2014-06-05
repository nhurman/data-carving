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
    m_similarities = 0;
}

TextViewWidget::~TextViewWidget()
{
    delete ui;
}

void TextViewWidget::setEncodings(QMap<QString, Encoding2*>* encodings)
{
    m_encodings = encodings;
    m_encoding = (*m_encodings)["Binary"];
}

void TextViewWidget::setSimilarities(std::list<std::pair<float, int>>* sims)
{
    m_similarities = sims;
    updateContents();
}

void TextViewWidget::setBitString(BitString const* bs)
{
    m_bitString = bs;
    updateContents();
}

QColor makeColor(QColor c1, QColor c2, float ratio)
{
    return QColor (c1.red()*ratio + c2.red()*(1-ratio),
                   c1.green()*ratio + c2.green()*(1-ratio),
                   c1.blue()*ratio + c2.blue()*(1-ratio));
}

QColor toSimColor(const float f)
{
    const char* DISSIM_COLOR = "red";
    const char* SIM_COLOR = "green";
    const char* OTHER_SIM_COLOR = "blue";
    if(f >= 0)
        return makeColor( QColor( SIM_COLOR ), QColor( DISSIM_COLOR ), f );
    //else
    return makeColor( QColor( OTHER_SIM_COLOR ), QColor( DISSIM_COLOR ), -f );
}

void TextViewWidget::updateContents()
{
    ui->textEdit->clear();
    m_encoding->setBitString(m_bitString);
    m_encoding->setGlobalOffset(m_globalOffset);

    QString contents = "<pre style='word-wrap:break-words;white-space:pre-wrap'>";
    int pos = -1;

    if (m_similarities) {
        for (std::pair<float, int> p: *m_similarities) {
            QColor color = toSimColor(p.first);

            contents += QString("<span style='color:rgb(%1, %2, %3)'>")
                .arg(color.red()).arg(color.green()).arg(color.blue());

            int newPos = p.second;

            if (newPos < 0) newPos = m_encoding->countChunks() - 1;
            for (int i = pos + 1; i <= newPos; ++i) {
                contents += QString(m_encoding->getChunk(i).c_str()).toHtmlEscaped();
            }

            contents += "</span>";
            pos = newPos;
        }
    }
    else for (unsigned int i = 0; i < m_encoding->countChunks(); ++i) {
        contents += QString(m_encoding->getChunk(i).c_str()).toHtmlEscaped();
    }

    ui->textEdit->setText(contents + "</pre>");
}

void TextViewWidget::on_encoding_currentIndexChanged(const QString &arg1)
{
    m_encoding = (*m_encodings)[arg1];
    emit encodingChanged();
    updateContents();
}

void TextViewWidget::on_globalOffset_valueChanged(int arg1)
{
    m_globalOffset = arg1;
    emit encodingChanged();
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

Encoding2* TextViewWidget::getEncoding() const
{
    return m_encoding;
}

int TextViewWidget::getOffset() const
{
    return m_globalOffset;
}
