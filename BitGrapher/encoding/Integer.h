#ifndef INTEGER_H
#define INTEGER_H

#include "encoding/Encoding2.h"

class Integer : public Encoding2
{
public:
    Integer();
    std::string getChunk(unsigned int index) const;
};

class Integer2 : public Integer
{
public:
    Integer2() : Integer() {}
    unsigned int bitsPerChunk() const { return 2; }
    std::string getName() const { return "Int2"; }
};

class Integer3 : public Integer
{
public:
    Integer3() : Integer() {}
    unsigned int bitsPerChunk() const { return 3; }
    std::string getName() const { return "Int3"; }
};

class Integer4 : public Integer
{
public:
    Integer4() : Integer() {}
    unsigned int bitsPerChunk() const { return 4; }
    std::string getName() const { return "Int4"; }
};

class Integer5 : public Integer
{
public:
    Integer5() : Integer() {}
    unsigned int bitsPerChunk() const { return 5; }
    std::string getName() const { return "Int5"; }
};

class Integer6 : public Integer
{
public:
    Integer6() : Integer() {}
    unsigned int bitsPerChunk() const { return 6; }
    std::string getName() const { return "Int6"; }
};

class Integer7 : public Integer
{
public:
    Integer7() : Integer() {}
    unsigned int bitsPerChunk() const { return 7; }
    std::string getName() const { return "Int7"; }
};

class Integer8 : public Integer
{
public:
    Integer8() : Integer() {}
    unsigned int bitsPerChunk() const { return 8; }
    std::string getName() const { return "Int8"; }
};

class Integer16 : public Integer
{
public:
    Integer16() : Integer() {}
    unsigned int bitsPerChunk() const { return 16; }
    std::string getName() const { return "Int16"; }
};

class Integer32 : public Integer
{
public:
    Integer32() : Integer() {}
    unsigned int bitsPerChunk() const { return 32; }
    std::string getName() const { return "Int32"; }
};

#endif // INTEGER_H
