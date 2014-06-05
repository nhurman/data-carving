#include "ASCII8.h"
#include <QDebug>

ASCII8::ASCII8() : Encoding2()
{

}

std::string ASCII8::getChunk(unsigned int index) const
{
    if (0 == m_bitString)
        return std::string();

    int startIndex = m_globalOffset + index * bitsPerChunk();
    char byte = 0;
    for (unsigned int i = startIndex; i < startIndex + bitsPerChunk() && i < m_bitString->size(); ++i) {
        byte = (byte << 1) | static_cast<int>((*m_bitString)[i]);
    }

    if (byte < 0x20) byte = ' '; // Control codes

    return std::string(&byte, 1);
}

unsigned int ASCII8::bitsPerChunk() const
{
    return 8;
}

std::string ASCII8::getName() const
{
    return "ASCII (8 bits)";
}
