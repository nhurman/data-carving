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
public:
    Dump();
    Dump(QString fileName);
    ~Dump();

    BitString* getBitString();
    QString getFileName();
    QString getShortName();

private:
    static QString shortenFileName(QString filePath);
    static QString shortenFileName(std::string fileName);
};

#endif // DUMP_H
