#ifndef ASCII8_H
#define ASCII8_H

#include "core/BitString.h"
#include "encoding/Encoding2.h"

/*!
 * \class ASCII8
 * \brief ASCII encoding over 8 bits
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
class ASCII8 : public Encoding2
{
public:
    ASCII8();
    std::string getChunk(unsigned int index) const;
    virtual unsigned int bitsPerChunk() const;
    virtual std::string getName() const;
};

#endif // ASCII8_H
