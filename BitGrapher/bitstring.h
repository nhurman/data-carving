#ifndef bitstring_H
#define bitstring_H

//#include "bitstring.h"

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

    void bitAnd(BitString const& bitstring);
    void bitOr(BitString const& bitstring);
    void bitXor(BitString const& bitstring);

    unsigned int hammingWeight() const;
    unsigned int hammingDistance(BitString const& bitstring) const;

    std::string toString() const;
    BitString substring(unsigned int start, size_t size) const;
    size_t size() const;
    bool equals(BitString const& bitstring) const;
    bool contains(BitString s) const;

private:
    size_t m_size;
    char* m_bytes;
};


#endif // bitstring_H
