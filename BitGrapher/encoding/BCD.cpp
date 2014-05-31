#include "BCD.h"
#include <algorithm>

BCD::BCD() : Encoding2()
{
}

std::string BCD::getChunk(unsigned int index) const
{
    if (0 == m_bitString)
        return std::string();

    int startIndex = m_globalOffset + index * bitsPerChunk();
    char byte = 0;
    for (unsigned int i = startIndex; i < startIndex + bitsPerChunk() && i < m_bitString->size(); ++i) {
        byte = (byte << 1) | static_cast<int>((*m_bitString)[i]);
    }

    byte += 0x30;
    return std::string(&byte, 1);
}

unsigned int BCD::bitsPerChunk() const
{
    return 6;
}

std::string BCD::getName() const
{
    return "BCD";
}
