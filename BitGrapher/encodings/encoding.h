#ifndef ENCODING_H
#define ENCODING_H

#include <sstream>
#include <string>
#include <iostream>
#include <QString>
#include "core/bitstring.h"

class Encoding
{
protected:
    QString m_encodingName;
    unsigned int m_globalOffset;
    unsigned int m_localOffset;
    unsigned int m_charSize;

public:
    Encoding(QString encodingName, int globalOffset, int localOffset, int charSize);

    QString getName();
    int getGlobalOffset();
    int getLocalOffset();
    int getCharSize();

    std::string encode(BitString b);
    static char toASCII(char c);
    static char switchEndian(char c);
    static char toHexadecimal(char c);
    static char reverseHexadecimal(char c);

};



#endif // ENCODING_H
