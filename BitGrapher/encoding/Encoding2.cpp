#include "Encoding2.h"

Encoding2::Encoding2()
{
    m_globalOffset = 0;
    m_bitString = 0;
}

Encoding2::~Encoding2()
{
}

void Encoding2::setGlobalOffset(unsigned int offset)
{
    m_globalOffset = offset;
}

void Encoding2::setBitString(BitString const* bitString)
{
    m_bitString = bitString;
}

unsigned int Encoding2::countChunks() const
{
    if (NULL == m_bitString) return 0;
    return ceil(static_cast<double>(m_bitString->size()) / bitsPerChunk());
}
