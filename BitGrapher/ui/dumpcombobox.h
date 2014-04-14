#ifndef DUMPCOMBOBOX_H
#define DUMPCOMBOBOX_H

#include <QComboBox>

class DumpComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit DumpComboBox(QWidget *parent = 0, int index = 0);

signals:
    void currentIndexChanged( int );

private slots:
    void onCurrentIndexChanged();

private:
    int m_index;

};

#endif // DUMPCOMBOBOX_H
