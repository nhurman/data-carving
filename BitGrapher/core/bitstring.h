#ifndef BITSTRING_H
#define BITSTRING_H

#include <string>

enum InputFormat {HEXADECIMAL, BINARY, RAW};

class BitString
{
public:
    BitString(size_t size = 0);
    BitString(BitString const& other);
    BitString& operator=(BitString const& other);
    static BitString fromBin(std::string str);
    static BitString fromHex(std::string str);
    static BitString fromRaw(std::string str);
    static BitString makeBitString(std::string str, InputFormat format = HEXADECIMAL);
    ~BitString();

    // Simple accessors
    size_t size() const;
    bool operator[](unsigned int index) const;
    bool set(unsigned int index, bool value);
    int getSize();

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

    static InputFormat guessFileInputFormat(std::string fileName);
    static InputFormat guessTextInputFormat(std::string text);
    static InputFormat stringToFormat(std::string formatStr);
    static std::string formatToString(InputFormat format);

private:
    size_t m_size;
    char*  m_bytes;
};

#endif // BITSTRING_H
