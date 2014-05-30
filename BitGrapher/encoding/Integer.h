#ifndef INTEGER_H
#define INTEGER_H

#include "encoding/Encoding2.h"

class Integer : public Encoding2
{
public:
    Integer();
    std::string getChunk(unsigned int index) const;
    virtual unsigned int bitsPerChunk() const = 0;
};

class Integer2 : public Integer
{
public:
    Integer2() : Integer() {}
    unsigned int bitsPerChunk() const { return 2; }
};

class Integer3 : public Integer
{
public:
    Integer3() : Integer() {}
    unsigned int bitsPerChunk() const { return 3; }
};

class Integer4 : public Integer
{
public:
    Integer4() : Integer() {}
    unsigned int bitsPerChunk() const { return 4; }
};

class Integer5 : public Integer
{
public:
    Integer5() : Integer() {}
    unsigned int bitsPerChunk() const { return 5; }
};

class Integer6 : public Integer
{
public:
    Integer6() : Integer() {}
    unsigned int bitsPerChunk() const { return 6; }
};

class Integer7 : public Integer
{
public:
    Integer7() : Integer() {}
    unsigned int bitsPerChunk() const { return 7; }
};

class Integer8 : public Integer
{
public:
    Integer8() : Integer() {}
    unsigned int bitsPerChunk() const { return 8; }
};

class Integer16 : public Integer
{
public:
    Integer16() : Integer() {}
    unsigned int bitsPerChunk() const { return 16; }
};

class Integer32 : public Integer
{
public:
    Integer32() : Integer() {}
    unsigned int bitsPerChunk() const { return 32; }
};

#endif // INTEGER_H
