#include "dumpset.h"

std::map<QString, DumpSet*> DumpSet::openedDumpSets;
int DumpSet::m_nbNewDumpSets;

DumpSet::DumpSet(QTreeWidgetItem* associatedItem) : m_associatedItem(associatedItem), m_dumps()
{
}

DumpSet::DumpSet() : m_dumps()
{
}

QTreeWidgetItem* DumpSet::addDump(QString fileName)
{
    QString shortName = shortenFileName(fileName);
    m_dumps[shortName] = Dump(fileName);
    if(m_associatedItem != NULL)
    {
        QTreeWidgetItem* i = new QTreeWidgetItem(QStringList(shortName));
        m_associatedItem->addChild(i);
        return i;
    }
    return NULL;
}

Dump* DumpSet::find(QString name)
{
    std::map<QString, Dump>::iterator i = m_dumps.find(name);
    if( i != m_dumps.end())
    {
        return &(i->second);
    }
    return NULL;
}

void DumpSet::remove(QString name)
{
    m_dumps.erase(name);
}

QString DumpSet::shortenFileName(QString fileName)
{
    return fileName.section('/',-1);
}

QString DumpSet::shortenFileName(std::string fileName)
{
    return QString::fromStdString(fileName).section('/',-1);
}
