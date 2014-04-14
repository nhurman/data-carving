#include "encodings/encoding.h"

Encoding::Encoding()
{
}

std::string Encoding::encode(BitString b, char (* encodeChar)(char c), int globalOffset, int charOffset, int charSize) {
    int i = globalOffset;
    unsigned char leftPart;
    unsigned char rightPart;
    int toEncode;
    std::stringstream ss;

    while (i + charSize <= b.size()) {

        leftPart = ((unsigned char) b.getByte(i)) / ((unsigned int) pow(2, (i%8))) % ((unsigned int) pow(2,charSize));
        rightPart = ((unsigned char) b.getByte(i+charSize)) % ((unsigned int) pow(2, (i%8))) << ((8-i%8));

        toEncode = (leftPart + rightPart)% ((unsigned int) pow(2,charSize));

        // For debug, let that here !
        //std::cout  << (unsigned int) leftPart << " " <<(unsigned int) rightPart << " " << (unsigned int) toEncode  << std::endl;

        ss << encodeChar(toEncode);
        i += charSize + charOffset;
    }
    return ss.str();
}

char Encoding::toASCII(char c){
    return static_cast<char>(c);
}


// Switch between Little Endian and Big Endian
char Encoding::switchEndian(char c) {
    return   ((c & 1) << 7)
           + ((c & 2) << 5)
           + ((c & 4) << 3)
           + ((c & 8) << 1)
           + ((c & 16) >> 1)
           + ((c & 32) >> 3)
           + ((c & 64) >> 5)
           + ((c & 128) >> 7);
}

char Encoding::toHexadecimal(char c) {
        if (c < 10)
            return c+48;
        else
            return c+55;
}

char Encoding::reverseHexadecimal(char c) {
    return toHexadecimal(((unsigned char) switchEndian(c)) >> 4);
}
