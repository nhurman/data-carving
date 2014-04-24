#include "encodings/encoding.h"

Encoding::Encoding(QString encodingName, int globalOffset, int localOffset, int charSize) :
    m_encodingName(encodingName), m_globalOffset(globalOffset), m_localOffset(localOffset), m_charSize(charSize)
{
}


QString Encoding::getName()
{
    return m_encodingName;
}

int Encoding::getGlobalOffset()
{
    return m_globalOffset;
}

int Encoding::getLocalOffset()
{
    return m_localOffset;
}

int Encoding::getCharSize()
{
    return m_charSize;
}


std::string Encoding::encode(BitString b) {
    int i = m_globalOffset;
    unsigned char leftPart;
    unsigned char rightPart;
    int toEncode;
    std::stringstream ss;
    char (*encodeChar)(char);

    if(m_encodingName == "Binary")
        return b.toString();
    else if(m_encodingName == "Hexadecimal")
        encodeChar =  Encoding::reverseHexadecimal;
    else
        encodeChar =  Encoding::toASCII;

    while (i + m_charSize <= b.size()) {

        leftPart = ((unsigned char) b.getByte(i)) / ((unsigned int) pow(2, (i%8))) % ((unsigned int) pow(2,m_charSize));
        rightPart = ((unsigned char) b.getByte(i+m_charSize)) % ((unsigned int) pow(2, (i%8))) << ((8-i%8));

        toEncode = (leftPart + rightPart)% ((unsigned int) pow(2,m_charSize));

        // For debug, let that here !
        //std::cout  << (unsigned int) leftPart << " " <<(unsigned int) rightPart << " " << (unsigned int) toEncode  << std::endl;

        ss << encodeChar(toEncode);
        i += m_charSize + m_localOffset;
    }
    return ss.str();
}

char Encoding::toASCII(char c){
    return static_cast<char>(c);
}

char Encoding::reverseASCII(char c){
    return toASCII(((unsigned char) switchEndian(c)) >> 4);
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
