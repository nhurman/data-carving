#ifndef ENCODING_H
#define ENCODING_H

#include <sstream>
#include <string>
#include <iostream>
#include "bitstring.h"

class Encoding
{
public:
    Encoding();

    static std::string encode(BitString b, char (*encodeChar)(int c), int globalOffset, int charOffset, int charSize);
    static char toASCII(int c);

};



#endif // ENCODING_H
