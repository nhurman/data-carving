#include "encoding.h"

Encoding::Encoding()
{
}

std::string Encoding::encode(BitString b, char (* encodeChar)(int c), int globalOffset, int charOffset, int charSize) {
    int i = globalOffset;
    char leftPart;
    char rightPart;
    int toEncode;
    std::stringstream ss;

    while (i + charSize <= b.size()) {

        leftPart = b.getByte(i) % 2^(8-i%8);
        rightPart = b.getByte(i+8) / 2^(8-i%8);
        std::cout << b.getByte(i) <<  " " << leftPart << " " << rightPart << std::endl;

        toEncode = (leftPart << (i%8)) + (rightPart >> (8-i%8));

        ss << encodeChar(toEncode);
        i += charSize + charOffset;
    }
    return ss.str();
}

char Encoding::toASCII(int c){
    return static_cast<char>(c);
}
