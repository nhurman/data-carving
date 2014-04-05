#include "dump.h"
#include <iostream>
#include <fstream>

Dump::Dump(QString fileName): m_fileName(fileName)
{
    std::ifstream f;
    f.open (fileName.toUtf8());
    std::string str = "";
    std::string buff = "";
    while(std::getline(f, buff))
    {
        str += buff;
    }
    m_bitstring = new BitString(str);
}

Dump::Dump()
{
}

Dump::~Dump()
{}

BitString* Dump::getBitString()
{
    return m_bitstring;
}

QString Dump::getFileName()
{
    return m_fileName;
}

QString Dump::getShortName()
{
    return shortenFileName(m_fileName);
}

QString Dump::shortenFileName(QString fileName)
{
    return fileName.section('/',-1);
}

QString Dump::shortenFileName(std::string fileName)
{
    return QString::fromStdString(fileName).section('/',-1);
}
