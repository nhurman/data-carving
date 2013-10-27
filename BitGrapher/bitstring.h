#ifndef BITSTRING_H
#define BITSTRING_H

#include "bitstring.h"

#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>

class BitString
{
public:
    BitString(size_t size);
    BitString(std::string str);
    ~BitString();

    bool get(unsigned int index) const;
    bool operator[](unsigned int index) const;
    bool set(unsigned int index, bool value);
    std::string toString() const;
    size_t size() const;

private:
    size_t m_size;
    char* m_bytes;
};


#endif // BITSTRING_H
