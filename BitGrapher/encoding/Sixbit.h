#ifndef SIXBIT_H
#define SIXBIT_H

#include <string>
#include <sstream>
#include <iomanip>
#include <QDebug>

#include "core/BitString.h"
#include "Encoding.h"

class Sixbit : public Encoding
{
public:
    Sixbit();
    Sixbit(BitString const* bs);
    ~Sixbit();
    std::string toHTML() const;
    size_t lines() const;

    size_t BytesPerLine() const;
    size_t LineHeight() const;
    size_t LineWidth() const;
    size_t BitPerChar() const;


};

#endif // SIXBIT_H
