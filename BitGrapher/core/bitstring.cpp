#include <algorithm>
#include <cstring>
#include <cmath>
#include <fstream>
#include <iostream>

#include "BitString.h"
#include "Exception.h"

BitString::BitString(size_t size) : m_size(size)
{
    int bytes = ceil(m_size / 8.);
    m_bytes = new char[bytes];
    memset(m_bytes, 0, bytes);
}

BitString::BitString(BitString const& other)
{
    operator=(other);
}

BitString& BitString::operator=(BitString const& other)
{
    delete[] m_bytes;
    m_size = other.m_size;
    m_bytes = new char[m_size / 8];
    memcpy(m_bytes, other.m_bytes, m_size / 8);
    return *this;
}

BitString BitString::fromHex(std::string str)
{
    // Remove spaces in str
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());

    // Incomplete string
    if (str.length() % 2 == 1) {
        std::string b = str.substr(str.length() - 1);
        str.erase(str.length() - 1);
        str.append("0" + b);
    }

    // Reserve memory    
    int bytes = str.length() / 2;
    BitString bs(bytes * 8);

    // Parse string
    for (unsigned int i = 0; i < str.length(); i += 2) {
        char byte = 0;
        for (int j = 0; j < 2; ++j) {
            char c = str[i + j];

            if (c >= 'a' && c <= 'f') {
                c -= 'a' - 'A';
            }
            if (c >= 'A' && c <= 'F') {
                c += 10 - 'A';
            }
            else if (c >= '0' && c <= '9') {
                c -= '0';
            }
            else {
                c =  0;
            }

            byte = byte * 16 + c;
        }

        bs.m_bytes[i / 2] = 0;
        for (int j = 0; j < 8; ++j) {
            if (byte & (1 << j)) {
                bs.m_bytes[i / 2] |= 1 << (7 - j);
            }
        }
    }

    return bs;
}

BitString BitString::fromBin(std::string str)
{
    // Remove spaces in str
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());

    BitString bs(str.size());
    for (unsigned int i = 0; i < str.size(); ++i) {
        bs.set(i, str[i] == '1');
    }

    return bs;
}

BitString BitString::fromRaw(std::string str)
{
    // Remove spaces in str
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());

    BitString bs(str.length()*8);
    for(unsigned int i = 0; i < str.length(); i++)
    {
        for(int j = 0; j < 8; j++)
        {
            bs.set(8*i+j, str[i] & (1 << (7-j)));
        }

    }

    return bs;
}

BitString BitString::makeBitString(std::string str, InputFormat format)
{
    switch(format)
    {
    case BINARY:
        return fromBin(str);
    case HEXADECIMAL:
        return fromHex(str);
    default: //RAW
        return fromRaw(str);
    }
}

BitString::~BitString()
{
    delete[] m_bytes;
}

// Simple accessors
size_t BitString::size() const
{
    return m_size;
}

// Get the bit at the index (starts at 0)
bool BitString::operator[](unsigned int index) const
{
    if (index >= m_size) {
        throw BitStringException("BitString::get out of bounds");
    }

    return m_bytes[index / 8] & (1 << (index % 8));
}

bool BitString::set(unsigned int index, bool value)
{
    if (index >= m_size) {
        throw BitStringException("BitString::set out of bounds");
    }

    if(value) {
        m_bytes[index / 8] |= 1 << (index % 8);
    }
    else {
        m_bytes[index / 8] &= ~(1 << (index % 8));
    }

    return value;
}

// Bitwise operators
BitString BitString::operator&(BitString const& other)
{
    BitString bs(m_size);
    for (unsigned int index = 0; index < m_size/8; ++index) {
        bs.m_bytes[index] = m_bytes[index] & other.m_bytes[index];
    }

    return bs;
}

BitString BitString::operator|(BitString const& other)
{
    BitString bs(m_size);
    for (unsigned int index = 0; index < m_size/8; ++index) {
        bs.m_bytes[index] = m_bytes[index] | other.m_bytes[index];
    }

    return bs;
}

BitString BitString::operator^(BitString const& other)
{

    BitString bs(m_size);
    for (unsigned int index = 0; index < m_size/8; ++index) {
        bs.m_bytes[index] = m_bytes[index] ^ other.m_bytes[index];
    }

    return bs;
}


// Operations
BitString BitString::substring(unsigned int start, size_t size) const
{
    BitString out(size);

    if (start + size > m_size) {
        throw BitStringException("BitString::substring overflow");
    }

    for (unsigned int index = 0; index < size; ++index) {
        out.set(index, (*this)[index + start]);
    }

    return out;
}

bool BitString::operator==(BitString const& other) const
{
    if (m_size != other.m_size) {
        return false;
    }

    unsigned int bytes = ceil(m_size / 8.);
    for (unsigned int i = 0; i < bytes; ++i) {
        if(m_bytes[i] != other.m_bytes[i]) {
            return false;
        }
    }

    return true;
}

bool BitString::operator!=(BitString const& other) const
{
    return !operator==(other);
}

bool BitString::contains(BitString const& bs) const
{
    size_t size = bs.size();

    if (size > m_size) {
        return false;
    }

    for (unsigned int i = 0 ; i < m_size - size + 1 ; ++i) {
        BitString sub = substring(i, size);
        if (sub == bs) {
            return true;
        }
    }

    return false;
}

std::string BitString::toString() const
{
    std::string out;
    for (unsigned int index = 0; index < m_size; ++index) {
        out += operator[](index) ? '1' : '0';
    }

    return out;
}

InputFormat BitString::guessFileInputFormat(std::string fileName)
{
    std::ifstream f;
    f.open (fileName);
    if(!f.is_open())
    {

        std::cout << "Unable to open dump : The following dump could not be opened :\n"+fileName << std::endl;
        return RAW;
    }

    InputFormat format = BINARY; //the lowest format, in terms of character usage
    std::string buff = "";
    while(std::getline(f, buff))
    {
        switch (guessTextInputFormat(buff))
        {
        case HEXADECIMAL:
            format = HEXADECIMAL; //hexadecimal < raw but raw would return immediately if detected
            break;

        case RAW:
            return RAW; //nothing greater than raw

        default:
            break;
        }
    }
    return format;
}

InputFormat BitString::guessTextInputFormat(std::string text)
{
    std::string str = text;
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
    InputFormat format = BINARY;; //the lowest format, in terms of character usage
    for(unsigned int i = 0; i < str.size(); i++)
    {
        if(str[i] != '0' && str[i] != '1') //not binary
        {
            if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'F') || (str[i] >= 'a' && str[i] <= 'f'))
                format = HEXADECIMAL; //hexadecimal < raw but raw would return immediately if detected
            else //any other character
                return RAW;
        }
    }
    return format;
}

InputFormat BitString::stringToFormat(std::string formatStr)
{
    if(formatStr == "Binary")
    {
        return BINARY;
    }
    else if(formatStr == "Hexadecimal")
    {
        return HEXADECIMAL;
    }
    else //Raw data
    {
        return RAW;
    }
}

std::string BitString::formatToString(InputFormat format)
{
    switch(format)
    {
    case BINARY:
        return "Binary";
    case HEXADECIMAL:
        return "Hexadecimal";
    default: //RAW
        return "Raw data";
    }
}
