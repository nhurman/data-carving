#ifndef BITSTRING_H
#define BITSTRING_H

#include <string>

class BitString
{
public:
    BitString(size_t size = 0);
    BitString(BitString const& other);
    BitString& operator=(BitString const& other);
    static BitString fromHex(std::string str);
    static BitString fromStr(std::string str);
    ~BitString();

    // Simple accessors
    size_t size() const;
    bool operator[](unsigned int index) const;
    bool set(unsigned int index, bool value);

    // Bitwise operators
    BitString operator&(BitString const& other);
    BitString operator|(BitString const& other);
    BitString operator^(BitString const& other);

    // Operations
    bool operator==(BitString const& other) const;
    bool operator!=(BitString const& other) const;
    BitString substring(unsigned int start, size_t size) const;
    bool contains(BitString const& bs) const;

    std::string toString() const;

private:
    size_t m_size;
    char*  m_bytes;
};

#endif // BITSTRING_H
