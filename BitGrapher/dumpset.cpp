#include "dumpset.h"
#include <iostream>
#include <fstream>

DumpSet::DumpSet(QString fileName) : m_dumps(), m_fileName(fileName), m_isModified(false)
{
    if(fileName != "") //existing dump
    {

        QString shortName = shortenFileName(fileName);

        std::ifstream f;
        f.open (fileName.toUtf8());
        if(f.is_open())
        {
            std::string buff = "";
            while(std::getline(f, buff))
            {
                addDump(QString::fromStdString(buff));
            }
        }
    }
    else //new dump
    {
        m_isModified = true;
    }
}

void DumpSet::setFileName(QString fileName)
{
    m_fileName = fileName;
}

QString DumpSet::getShortName()
{
    return shortenFileName(m_fileName);
}

bool DumpSet::hasName()
{
    return m_fileName.size() != 0;
}

bool DumpSet::isModified()
{
    return m_isModified;
}

void DumpSet::addDump(QString fileName)
{
    addDump(Dump(fileName));
}

void DumpSet::addDump(Dump d)
{
    QString shortName = shortenFileName(d.getFileName());
    m_dumps[shortName] = d;
    m_isModified = true;
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
    m_isModified = true;
}

std::vector<QString> DumpSet::getDumpNames()
{
    std::vector<QString> v;
    for(std::map<QString,Dump>::iterator it = m_dumps.begin(); it != m_dumps.end(); ++it) {
      v.push_back(it->first);
    }
    return v;
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
    m_isModified = false;

    return true;
}

bool DumpSet::save()
{
    return saveToFile(m_fileName);
}

QString DumpSet::shortenFileName(QString fileName)
{
    return fileName.section('/',-1);
}

QString DumpSet::shortenFileName(std::string fileName)
{
    return QString::fromStdString(fileName).section('/',-1);
}
