#ifndef ASCII7_H
#define ASCII7_H

#include "encoding/ASCII8.h"

/*!
 * \class ASCII7
 * \brief ASCII encoding over 7 bits
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
class ASCII7 : public ASCII8
{
public:
    ASCII7();
    unsigned int bitsPerChunk() const;
    std::string getName() const;
};

#endif // ASCII7_H
