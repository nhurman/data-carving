#ifndef BINARY_H
#define BINARY_H

#include "core/BitString.h"
#include "encoding/Encoding2.h"

class Binary : public Encoding2
{
public:
    Binary();
    std::string getChunk(unsigned int index) const;
    unsigned int bitsPerChunk() const;
    std::string getName() const;
};

#endif // BINARY_H
