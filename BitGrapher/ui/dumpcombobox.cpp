#include "ui/dumpcombobox.h"

DumpComboBox::DumpComboBox(QWidget *parent, int index) : QComboBox(parent), m_index(index)
{
    QObject::connect(this, SIGNAL(currentIndexChanged( QString ) ),
            this, SLOT(onCurrentIndexChanged( )));
}


void DumpComboBox::onCurrentIndexChanged()
{
    emit currentDumpChanged(m_index);
}
