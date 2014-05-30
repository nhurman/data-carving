#ifndef ASCII7_H
#define ASCII7_H

#include "encoding/ASCII8.h"

class ASCII7 : public ASCII8
{
public:
    ASCII7();
    unsigned int bitsPerChunk() const;
};

#endif // ASCII7_H
