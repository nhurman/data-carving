#ifndef ENCODING2_H
#define ENCODING2_H

#include "core/BitString.h"

class Encoding2
{
public:
    Encoding2();
    virtual ~Encoding2();
    void setGlobalOffset(unsigned int offset);
    void setBitString(BitString const* bitString);
    unsigned int countChunks() const;
    virtual std::string getChunk(unsigned int index) const = 0;
    virtual unsigned int bitsPerChunk() const = 0;

protected:
    BitString const* m_bitString;
    unsigned int m_globalOffset;
};

#endif // ENCODING2_H
