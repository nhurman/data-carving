#include <iostream>
#include <fstream>

#include "Exception.h"
#include "Dump.h"

Dump::Dump(std::string const& filePath): m_filePath(filePath)
{
    std::ifstream f;
    f.open(m_filePath.c_str());
    if (!f.is_open()) {
        throw IOException("Could not open dump " + m_filePath);
    }

    std::string str, buff;
    while(std::getline(f, buff)) {
        str.append(buff);
    }

    m_bitString = BitString::fromHex(str);
}

Dump::Dump(Dump const& other) : m_filePath(other.m_filePath)
{
    std::ifstream f;
    f.open(m_filePath.c_str());
    if (!f.is_open()) {
        throw IOException("Could not open dump " + m_filePath);
    }

    std::string str, buff;
    while(std::getline(f, buff)) {
        str.append(buff);
    }

    m_bitString = BitString::fromHex(str);
}

BitString const* Dump::bitString() const
{
    return &m_bitString;
}

std::string Dump::filePath() const
{
    return m_filePath;
}

std::string Dump::fileName() const
{
    size_t pos = m_filePath.find_last_of('/');
    if (std::string::npos == pos) {
        return m_filePath;
    }

    return m_filePath.substr(pos + 1);
}
