#ifndef DUMP_H
#define DUMP_H

#include <cstring>
#include "bitstring.h"

class Dump
{
protected:
    BitString m_bitstring;
public:
    Dump(std::string fileName);
    ~Dump();

    BitString* getBitString();
};

#endif // DUMP_H
