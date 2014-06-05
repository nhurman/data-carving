#include "Dump.h"

Dump::Dump(std::string const& filePath, InputFormat format): m_filePath(filePath), m_format(format)
{
    std::ifstream f;
    f.open(m_filePath.c_str());
    if (!f.is_open()) {
        throw IOException("Could not open dump " + m_filePath);
    }

    std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    m_bitString = BitString::makeBitString(str, format);
}

Dump::Dump(Dump const& other) : m_filePath(other.m_filePath), m_format(other.m_format)
{
    std::ifstream f;
    f.open(m_filePath.c_str(), std::ios::binary | std::ios::in);
    if (!f.is_open()) {
        throw IOException("Could not open dump " + m_filePath);
    }

    std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    m_bitString = BitString::makeBitString(str, m_format);
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

InputFormat Dump::getFormat() const
{
    return m_format;
}

int Dump::getSize() const
{
    return m_bitString.size();
}
