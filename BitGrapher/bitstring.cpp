#include "bitstring.h"
#include <iostream>
#include <iomanip>


BitString::BitString(size_t size) : m_size(size)
{
    int bytes = ceil(m_size / 8.);
    m_bytes = new char[bytes];
    memset(m_bytes, 0, bytes);
}

//Creates a BitString from an hexadecimal string
BitString::BitString(std::string str)
{
    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
    if (str.length() % 2 == 1) {
        str.append("0");
    }

    int bytes = str.length() / 2;
    m_size = bytes * 8;
    m_bytes = new char[bytes];

    for (unsigned int i = 0; i < str.length(); i += 2) {
        char byte = 0;
        for (int j = 0; j < 2; ++j) {
            char c = str[i + j];

            if (c >= 'a' && c <= 'f') {
                c -= 'a' - 'A';
            }
            if (c >= 'A' && c <= 'F') {
                c += 10 - 'A';
            }
            else if (c >= '0' && c <= '9') {
                c -= '0';
            }
            else {
                c =  0;
            }

            byte = byte * 16 + c;
        }

        m_bytes[i / 2] = 0;
        for (int j = 0; j < 8; ++j) {
            if (byte & (1 << j)) {
                m_bytes[i / 2] |= 1 << (7 - j);
            }
        }
    }
}

BitString::~BitString()
{
    //delete[] m_bytes; //<-- This caused an error on run (debug assertion failed)
}

size_t BitString::size() const
{
    return m_size;
}

// Give the bit at position index; the first bit is index 0
bool BitString::get(unsigned int index) const
{
    return m_bytes[index / 8] & (1 << (index % 8));
}

bool BitString::operator[](unsigned int index) const
{
    return get(index);
}

bool BitString::set(unsigned int index, bool value)
{
    if(value)
        m_bytes[index / 8] |= 1 << (index % 8);
    else
        m_bytes[index / 8] &= ~(1 << (index % 8));

    return value;
}

// ne
void BitString::bitAnd(BitString const& bitstring)
{
    for (unsigned int index = 0; index < m_size/8; ++index) {
        m_bytes[index] = m_bytes[index] & bitstring.m_bytes[index];
    }
}

void BitString::bitOr(BitString const& bitstring)
{
    for (unsigned int index = 0; index < m_size/8; ++index) {
        m_bytes[index] = m_bytes[index] | bitstring.m_bytes[index];
    }
}

void BitString::bitXor(BitString const& bitstring)
{
    for (unsigned int index = 0; index < m_size/8; ++index) {
        m_bytes[index] = m_bytes[index] ^ bitstring.m_bytes[index];
    }
}


unsigned int BitString::hammingWeight() const
{
    unsigned int result = 0;

    for (unsigned int index = 0; index < m_size; ++index) {
        if (m_bytes[index / 8] & (1 << index % 8)){
            result++;
        }
    }

    return result;
}
// do the hamming weight on a substring of nbBit starting at index
unsigned int BitString::hammingWeight(unsigned int index, unsigned int nbBit) const {
    BitString b = this->substring(index, nbBit);
    return b.hammingWeight();
}

unsigned int BitString::hammingDistance(BitString const& bitstring) const
{
    unsigned int result = 0;

    // If both BitStrings don't have the same size, we can't process their Hamming distance
    if (m_size != bitstring.m_size){
        // we could also add max(m_size, bitstring.m_size) - min(m_size, bitstring.m_size)
        return -1;
    }

    for (unsigned int index = 0; index < m_size; ++index) {
        int a = m_bytes[index / 8] & (1 << index % 8);
        int b = bitstring.m_bytes[index / 8] & (1 << index % 8);
        // they have to be different, not equal
        if (a != b){
            result++;
        }
    }
    return result;
}


std::string BitString::toString() const
{
    std::string out;
    for (unsigned int index = 0; index < m_size; ++index) {
        out += (m_bytes[index / 8] & (1 << index % 8)) ? '1' : '0';
        if (index % 8 == 7 && index < m_size) {
            out += ' ';
        }
    }

    return out;
}

BitString BitString::substring(unsigned int start, size_t size) const
{
    BitString out(size);

    for (unsigned int index = 0; index < size; ++index) {
        if(m_bytes[(index+start) / 8] & (1 << (index+start) % 8))
            out.set(index, 1);
        else
            out.set(index, 0);
    }

    return out;
}

bool BitString::equals(BitString const& bitstring) const
{
    for (unsigned int i = 0; i < m_size/8; ++i) {
        if(m_bytes[i] != bitstring.m_bytes[i])
            return false;
    }
    return true;
}

bool BitString::contains(BitString s) const
{
    size_t size = s.size();
    for(unsigned int i=0 ; i < m_size-size+1 ; i++) {
        BitString sub = this->substring(i, size);
        if(sub.equals(s))
            return true;
    }
    return false;
}


//Return a list with all the diagonals, without doubles
std::list<Diagonal> BitString::dotPlotPattern(BitString dump) const {
    std::list<Diagonal> listDiag;
    unsigned int z;

    for (unsigned int y = 0; y <= dump.m_size - MIN_DIAG_SIZE ; y++){
        for (unsigned int x = 0; x <= this->m_size - MIN_DIAG_SIZE; x++ ){
            if (( x!= 0 && y != 0) ? ((dump.m_bytes[(y-1) / 8] & (1 << ((y-1) % 8))) != (this->m_bytes[(x-1) / 8] & (1 << ((x-1) % 8)))) : 1) {
                for( z = 0; x+z < this->m_size && y+z < dump.m_size ; z++){
                    if (!((dump.m_bytes[(y+z) / 8] & (1 << ((y+z) % 8))) == (this->m_bytes[(x+z) / 8] & (1 << ((x+z) % 8))))) {
                       break;
                    }
                }
                if (z >= MIN_DIAG_SIZE) {
                    listDiag.push_back(Diagonal(x, y, z));
                }
            }
        }
    }
    return listDiag;
}

std::list<Diagonal> BitString::dotPlotPattern() const {
    std::list<Diagonal> listDiag;
    unsigned int z;

    listDiag.push_back(Diagonal(0, 0, m_size));

    for (unsigned int y = 0; y <= m_size - MIN_DIAG_SIZE ; y++){
        for (unsigned int x = 0; x < y; x++ ){
            if (( x!= 0) ? ((m_bytes[(y-1) / 8] & (1 << ((y-1) % 8))) != (m_bytes[(x-1) / 8] & (1 << ((x-1) % 8)))) : 1) {
                for( z = 0; x+z < m_size && y+z < m_size ; z++){
                    if (!((m_bytes[(y+z) / 8] & (1 << ((y+z) % 8))) == (m_bytes[(x+z) / 8] & (1 << ((x+z) % 8))))) {
                       break;
                    }
                }
                if (z >= MIN_DIAG_SIZE) {
                    listDiag.push_back(Diagonal(x, y, z));
                    listDiag.push_back(Diagonal(y, x, z));
                }
            }
        }
    }
    return listDiag;
}

std::list<std::pair<int,int> > BitString::similarities(BitString b1, BitString b2)
{
    std::list<std::pair<int,int> > sim;
    int start = -1;
    int max = std::max(b1.m_size, b2.m_size) - MIN_SIM_SIZE;
    for (int i = 0; i <= max ; i++){
        if(b1[i]==b2[i])
        {
            if(start == -1)
                start = i;
        }
        else
        {
            if(start != -1)
            {
                if(i-start >= MIN_SIM_SIZE)
                {
                    sim.push_back(std::pair<int,int>(start, i-1));
                }
                start = -1;
            }
        }
    }
    return sim;
}
