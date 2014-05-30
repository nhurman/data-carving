#include "Integer.h"

#include <QDebug>

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
        number = (number * 2) + static_cast<int>((*m_bitString)[i]);
    }

    unsigned int maxDigits = ceil(log10(pow(2., bitsPerChunk())));
    char buffer[maxDigits + 2];
    char fmt[5];
    sprintf(fmt, "%%%du", maxDigits + 1);
    sprintf(buffer, fmt, number);

    return std::string(buffer);
}
