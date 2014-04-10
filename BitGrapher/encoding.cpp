#include "encoding.h"

Encoding::Encoding()
{
}

std::string Encoding::encode(BitString b, char (* encodeChar)(char c), int globalOffset, int charOffset, int charSize) {
    int i = globalOffset;
    unsigned char leftPart;
    unsigned char rightPart;
    int toEncode;
    std::stringstream ss;

    int pika;

    while (i + charSize <= b.size()) {

        pika = 1;

        leftPart = ((unsigned char) b.getByte(i)) / ((unsigned int) pow(2, (i%8)));
        rightPart = ((unsigned char) b.getByte(i+8)) % ((unsigned int) pow(2, (i%8))) << ((8-i%8));

       toEncode = (leftPart ) + (rightPart );

        std::cout << pika << " " << (unsigned int) leftPart << " " <<(unsigned int) rightPart << " " << (unsigned int) toEncode  << std::endl;

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

