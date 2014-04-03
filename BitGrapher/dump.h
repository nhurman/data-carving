#ifndef DUMP_H
#define DUMP_H

#include <cstring>
#include "bitstring.h"
#include <QString>

class Dump
{
protected:
    BitString m_bitstring;
    QString m_fileName;
public:
    Dump();
    Dump(QString fileName);
    ~Dump();

    BitString* getBitString();
    QString getFileName();
};

#endif // DUMP_H
