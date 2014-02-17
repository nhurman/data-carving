#include "bitstring.h"
#include <iostream>
#include <iomanip>

BitString::BitString(size_t size) : m_size(size)
{
    int bytes = ceil(m_size / 8.);
    m_bytes = new char[bytes];
    memset(m_bytes, 0, bytes);
}

//Creates a BitString from an hexadecimal string
BitString::BitString(std::string str)
{
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
    if (str.length() % 2 == 1) {
        str.append("0");
    }

    int bytes = str.length() / 2;
    m_size = bytes * 8;
    m_bytes = new char[bytes];

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

        m_bytes[i / 2] = 0;
        for (int j = 0; j < 8; ++j) {
            if (byte & (1 << j)) {
                m_bytes[i / 2] |= 1 << (7 - j);
            }
        }
    }
}

BitString::~BitString()
{
    delete[] m_bytes;
}

size_t BitString::size() const
{
    return m_size;
}

bool BitString::get(unsigned int index) const
{
    return m_bytes[index / 8] & (1 << (index % 8));
}

bool BitString::operator[](unsigned int index) const
{
    return get(index);
}

bool BitString::set(unsigned int index, bool value)
{
    if(value)
        m_bytes[index / 8] |= 1 << (index % 8);
    else
        m_bytes[index / 8] &= ~(1 << (index % 8));

    return value;
}

std::string BitString::toString() const
{
    std::string out;
    for (unsigned int index = 0; index < m_size; ++index) {
        out += (m_bytes[index / 8] & (1 << index % 8)) ? '1' : '0';
        if (index % 8 == 7 && index < m_size) {
            out += ' ';
        }
    }

    return out;
}

BitString BitString::substring(unsigned int start, size_t size) const
{
    BitString out(size);

    for (unsigned int index = 0; index < size; ++index) {
        if(m_bytes[(index+start) / 8] & (1 << (index+start) % 8))
            out.set(index, 1);
        else
            out.set(index, 0);
    }

    return out;
}

bool BitString::equals(BitString const& bitstring) const
{
    for (unsigned int i = 0; i < m_size/8; ++i) {
        if(m_bytes[i] != bitstring.m_bytes[i])
            return false;
    }
    return true;
}

bool BitString::contains(BitString s) const
{
    size_t size = s.size();
    for(unsigned int i=0 ; i < m_size-size+1 ; i++) {
        BitString sub = this->substring(i, size);
        if(sub.equals(s))
            return true;
    }
    return false;
}

