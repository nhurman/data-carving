#include "ASCII7.h"

ASCII7::ASCII7()
{
}

unsigned int ASCII7::bitsPerChunk() const
{
    return 7;
}

std::string ASCII7::getName() const
{
    return "ASCII (7 bits)";
}
