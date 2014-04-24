#include "core/dump.h"
#include <iostream>
#include <fstream>
#include <QMessageBox>

Dump::Dump(QString fileName, InputFormat format): m_fileName(fileName)
{
    std::ifstream f;
    f.open (fileName.toUtf8());
    if(!f.is_open())
    {

        QMessageBox::warning(NULL, QString("Unable to open dump"),
                                 "The following dump could not be opened :\n"+fileName,
                                 QMessageBox::Ok);
        return;
    }
    std::string str = "";
    std::string buff = "";
    while(std::getline(f, buff))
    {
        str += buff;
    }
    m_bitstring = new BitString(str, format);
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
