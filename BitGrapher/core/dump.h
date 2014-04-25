#ifndef DUMP_H
#define DUMP_H

#include <cstring>
#include "bitstring.h"
#include <QString>

class Dump
{
protected:
    BitString* m_bitstring;
    QString m_fileName;
    InputFormat m_format;
public:
    Dump();
    Dump(QString fileName, InputFormat format = RAW);
    ~Dump();

    BitString* getBitString();
    QString getFileName();
    QString getShortName();
    InputFormat getFormat() { return m_format; }
    int getSize() { return m_bitstring->getSize(); }

private:
    static QString shortenFileName(QString filePath);
    static QString shortenFileName(std::string fileName);
};

#endif // DUMP_H
