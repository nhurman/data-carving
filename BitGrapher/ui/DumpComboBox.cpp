#include "ui/DumpComboBox.h"

DumpComboBox::DumpComboBox(QWidget *parent) : QComboBox(parent)
{
    //QObject::connect(this, SIGNAL(currentIndexChanged( QString ) ),
    //        this, SLOT(onCurrentIndexChanged( )));
}

void DumpComboBox::setDumpList(std::vector<const Dump *> dumps)
{
    Dump const* selection = currentDump();

    clear();
    m_dumps = dumps;
    QStringList dumpNames;
    for(unsigned int i = 0; i < m_dumps.size(); i++) //std::list to QStringList
    {
        dumpNames.push_back(QString::fromStdString(m_dumps.at(i)->fileName()));
    }
    addItems(dumpNames);

    //puts the selection back if possible
    std::vector<Dump const*>::iterator it = std::find(m_dumps.begin(), m_dumps.end(), selection);

    if ( it != m_dumps.end() )
        setCurrentIndex( std::distance(m_dumps.begin(), it) );
    else
        setCurrentIndex(0);
}

const Dump *DumpComboBox::currentDump()
{
    int index = currentIndex();
    if(index >= m_dumps.size() || index == -1)
        return NULL;
    //else
    return m_dumps.at(index);
}

//void DumpComboBox::onCurrentIndexChanged()
//{
//    m_index = currentIndex();
//    emit currentDumpChanged(m_index);
//}
