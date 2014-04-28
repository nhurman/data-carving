#ifndef bitstring_H
#define bitstring_H

//#include "bitstring.h"
#include "algorithms/diagonal.h"
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <list>
#include <map>

#define MIN_DIAG_SIZE 6
#define MIN_SIM_SIZE 4

enum InputFormat {HEXADECIMAL, BINARY, RAW};

class BitString
{
public:
    BitString(size_t size);
    BitString(std::string str, InputFormat format = HEXADECIMAL);
    ~BitString();

    bool get(unsigned int index) const;
    char getByte(unsigned int index) const;
    bool operator[](unsigned int index) const;
    bool set(unsigned int index, bool value);
    int getSize() { return m_size; }

    void bitAnd(BitString const& bitstring);
    void bitOr(BitString const& bitstring);
    void bitXor(BitString const& bitstring);

    unsigned int hammingWeight() const;
    unsigned int hammingWeight(unsigned int index, unsigned int nbBit) const;
    unsigned int hammingDistance(BitString const& bitstring) const;


    std::string toString() const;
    BitString substring(unsigned int start, size_t size) const;
    size_t size() const;
    bool equals(BitString const& bitstring) const;
    bool contains(BitString s) const;

    std::list<Diagonal> dotPlotPattern(const BitString *dump) const;
    std::list<Diagonal>dotPlotPattern() const;

    static std::list<std::pair<int,int> > similarities(BitString b1, BitString b2, int minSize = MIN_SIM_SIZE);

    static InputFormat guessFileInputFormat(std::string fileName);
    static InputFormat guessTextInputFormat(std::string text);
    static InputFormat stringToFormat(std::string formatStr);
    static std::string formatToString(InputFormat format);

    //convert between byte pos and char pos in string (because of blanks between bytes)
    static int convertCoords(int pos);

private:
    size_t m_size;
    char* m_bytes;
};


#endif // bitstring_H
