#include "dump.h"
#include <iostream>
#include <fstream>

Dump::Dump(QString fileName): m_fileName(fileName),
    m_bitstring("404")
{
    //FILE* f = fopen(fileName.c_str(), "r");
    std::ifstream f;
    f.open (fileName.toUtf8());
    std::string str = "";
    std::string buff = "";
    while(std::getline(f, buff))
    {
        str += buff;
    }
    m_bitstring = BitString(str);
}

Dump::Dump() :
        m_bitstring("404")
{
}

Dump::~Dump()
{}

BitString* Dump::getBitString()
{
    return &m_bitstring;
}

QString Dump::getFileName()
{
    return m_fileName;
}
