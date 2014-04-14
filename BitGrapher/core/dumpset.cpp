#include "core/dumpset.h"
#include <iostream>
#include <fstream>
#include <QMessageBox>

DumpSet::DumpSet(QString fileName) : m_dumps(), m_fileName(fileName), m_modified(false)
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
            m_modified = false;
        }
        else //could not open file
        {

            QMessageBox::warning(NULL, "Unable to open dump set",
                                     "The following dump set could not be opened :\n"+fileName,
                                     QMessageBox::Ok);
            m_modified = true;
            return;
        }
    }
    else //new dump
    {
        m_modified = true;
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
    return m_modified;
}

void DumpSet::addDump(QString fileName)
{
    addDump(Dump(fileName));
}

void DumpSet::addDump(Dump d)
{
    QString shortName = shortenFileName(d.getFileName());
    m_dumps[shortName] = d;
    m_modified = true;
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
    m_modified = true;
}

std::vector<QString> DumpSet::getDumpNames()
{
    std::vector<QString> v;
    for(std::map<QString,Dump>::iterator it = m_dumps.begin(); it != m_dumps.end(); ++it) {
      v.push_back(it->first);
    }
    return v;
}

int DumpSet::getDumpCount()
{
    return m_dumps.size();
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
    m_modified = false;

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

size_t DumpSet::size() {
    return m_dumps.size();
}

std::map<QString, Dump> DumpSet::getDumps(){
    return m_dumps;
}
