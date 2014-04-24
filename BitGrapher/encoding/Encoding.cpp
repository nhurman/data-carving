#include "Encoding.h"

Encoding::Encoding() : m_bitString(NULL)
{

}

Encoding::Encoding(BitString const* bs) : m_bitString(bs)
{

}

void Encoding::setBitString(BitString const* bs)
{
    m_bitString = bs;
}

BitString const* Encoding::bitString() const
{
    return m_bitString;
}
