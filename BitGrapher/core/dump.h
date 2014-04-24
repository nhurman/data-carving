#ifndef DUMP_H
#define DUMP_H

#include <string>
#include "BitString.h"

class Dump
{
public:
    Dump(std::string const& filePath);
    Dump(Dump const& other);
    BitString const* bitString() const;
    std::string filePath() const;
    std::string fileName() const;

private:
    BitString m_bitString;
    std::string m_filePath;
};

#endif // DUMP_H
