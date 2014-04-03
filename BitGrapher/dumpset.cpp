#include "dumpset.h"
#include <iostream>
#include <fstream>

std::map<QString, DumpSet*> DumpSet::m_openedDumpSets;
int DumpSet::m_nbNewDumpSets;

DumpSet::DumpSet(QTreeWidgetItem* associatedItem, QString fileName) : m_associatedItem(associatedItem), m_fileName(fileName)
{
}

DumpSet::DumpSet(QString fileName) : m_dumps(), m_fileName(fileName)
{
}

void DumpSet::setFileName(QString fileName)
{
    m_fileName = fileName;
}

bool DumpSet::hasName()
{
    return m_fileName.size() != 0;
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


bool DumpSet::saveToFile(QString filePath)
{
    std::ofstream file;
    file.open (filePath.toUtf8());
    if(!file.is_open())
        return false;
    for(std::map<QString, Dump>::iterator i = m_dumps.begin(); i != m_dumps.end(); i++)
    {
        file << i->second.getFileName().toStdString() << std::endl;
    }
    file.close();

    changeFileName(filePath);

    return true;
}

bool DumpSet::save()
{
    return saveToFile(m_fileName);
}

void DumpSet::changeFileName(QString name)
{
    DumpSet::m_openedDumpSets.erase(shortenFileName(m_fileName));
    m_fileName = name;
    QString shortName = shortenFileName(name);
    m_associatedItem->setText(0, shortName);
    DumpSet::m_openedDumpSets[shortName] = this;
}

QString DumpSet::shortenFileName(QString fileName)
{
    return fileName.section('/',-1);
}

QString DumpSet::shortenFileName(std::string fileName)
{
    return QString::fromStdString(fileName).section('/',-1);
}
