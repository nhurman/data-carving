#include "dump.h"

Dump::Dump(std::string fileName) :
        m_bitstring("")
{
}

Dump::~Dump()
{}

BitString* Dump::getBitString()
{
    return &m_bitstring;
}
