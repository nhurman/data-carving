#ifndef TEXTVIEWWIDGET_H
#define TEXTVIEWWIDGET_H

#include <QWidget>
#include "core/BitString.h"
#include "core/Label.h"
#include "encoding/Encoding2.h"

namespace Ui {
class TextViewWidget;
}

class TextViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TextViewWidget(QWidget *parent = 0);
    ~TextViewWidget();
    void setBitString(BitString const* bs);

signals:
    void labelAdded(Label l);

private slots:
    void on_encoding_currentIndexChanged(const QString &arg1);

    void on_globalOffset_valueChanged(int arg1);

    void on_newLabel_clicked();

private:
    void updateContents();
    Ui::TextViewWidget *ui;
    BitString const* m_bitString;
    Encoding2 *m_encoding;
    unsigned int m_globalOffset;
};

#endif // TEXTVIEWWIDGET_H
