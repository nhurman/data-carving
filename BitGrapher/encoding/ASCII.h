#ifndef ASCII_H
#define ASCII_H

#include <string>
#include "core/BitString.h"
#include "Encoding.h"

class ASCII : public Encoding
{
public:
    ASCII();
    ASCII(BitString const* bs);
    ~ASCII();
    std::string toHTML() const;
    size_t lines() const;

    size_t BytesPerLine() const;
    size_t LineHeight() const;
    size_t LineWidth() const;
};

#endif // ASCII_H
