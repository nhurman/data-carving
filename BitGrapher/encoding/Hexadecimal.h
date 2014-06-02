#ifndef HEXADECIMAL_H
#define HEXADECIMAL_H

#include <string>
#include <sstream>
#include <iomanip>
#include <QDebug>

#include "core/BitString.h"
#include "Encoding.h"

/*!
 * \class Hexadecimal
 * \brief Deprecated, please use Hexadecimal2 instead
 *
 * \author Nicolas Hurman
 * \date 02/03/2014
 */
class Hexadecimal : public Encoding
{
public:
    Hexadecimal();
    Hexadecimal(BitString const* bs);
    ~Hexadecimal();
    std::string toHTML() const;
    size_t lines() const;

    size_t BytesPerLine() const;
    size_t LineHeight() const;
    size_t LineWidth() const;
};

#endif // HEXADECIMAL_H
