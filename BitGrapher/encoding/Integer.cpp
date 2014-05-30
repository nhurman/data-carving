#include "Integer.h"

Integer::Integer() : Encoding2()
{
}

std::string Integer::getChunk(unsigned int index) const
{
    if (0 == m_bitString)
        return std::string();

    int startIndex = m_globalOffset + index * bitsPerChunk();
    unsigned int number = 0;
    for (unsigned int i = startIndex; i < startIndex + bitsPerChunk() && i < m_bitString->size(); ++i) {
        number = (number << 1) | static_cast<int>((*m_bitString)[i]);
    }

    char buffer[11];
    sprintf(buffer, " %u", number);
    return std::string(buffer);
}
