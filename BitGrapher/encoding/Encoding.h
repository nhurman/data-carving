#ifndef ENCODING_H
#define ENCODING_H

#include <core/BitString.h>

/*!
 * \class Encoding
 * \brief Deprecated, please use Encoding2 instead
 *
 * \author Nicolas Hurman
 * \date 02/03/2014
 */
class Encoding
{
public:
    Encoding();
    Encoding(BitString const* bs);
    virtual ~Encoding() {}
    void setBitString(BitString const* bs);
    BitString const* bitString() const;
    virtual std::string toHTML() const = 0;
    virtual size_t lines() const = 0;

    virtual size_t BytesPerLine() const = 0;
    virtual size_t LineHeight() const = 0;
    virtual size_t LineWidth() const = 0;

protected:
    BitString const* m_bitString;
};

#endif // ENCODING_H
