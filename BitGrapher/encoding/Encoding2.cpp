#include "Encoding2.h"
#include <QDebug>

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

std::string Encoding2::decode(unsigned int start, unsigned int length)
{
    unsigned int chunk = start / bitsPerChunk();
    unsigned int chunks = ceil(static_cast<double>(length) / bitsPerChunk());
    unsigned int offset = m_globalOffset;
    m_globalOffset = start % bitsPerChunk();
    std::string out;

    for (unsigned int i = chunk; i < chunk + chunks; ++i) {
        out += getChunk(i);
    }

    m_globalOffset = offset;
    return out;
}

unsigned int Encoding2::countChunks() const
{
    if (NULL == m_bitString) return 0;
    return ceil(static_cast<double>(m_bitString->size()) / bitsPerChunk());
}
