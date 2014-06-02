#ifndef ASCII_H
#define ASCII_H

#include <string>
#include <sstream>
#include <iomanip>
#include <QDebug>

#include "core/BitString.h"
#include "Encoding.h"

/*!
 * \class Encoding
 * \brief Deprecated, please use ASCII8 instead
 *
 * \author Nicolas Hurman
 * \date 02/03/2014
 */
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

    size_t BitPerChar() const;

};

#endif // ASCII_H
