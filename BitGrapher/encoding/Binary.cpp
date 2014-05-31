#include "Binary.h"

Binary::Binary() : Encoding2()
{
}

std::string Binary::getChunk(unsigned int index) const
{
    if (NULL == m_bitString)
        return std::string();

    index += m_globalOffset;
    if (index >= m_bitString->size())
        return "?";

    return m_bitString->operator[](index) ? "1" : "0";
}

unsigned int Binary::bitsPerChunk() const
{
    return 1;
}

std::string Binary::getName() const
{
    return "Binary";
}
