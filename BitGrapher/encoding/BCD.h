#ifndef BCD_H
#define BCD_H

#include "core/BitString.h"
#include "encoding/Encoding2.h"

/*!
 * \class BCD
 * \brief BCD encoding
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
class BCD : public Encoding2
{
public:
    BCD();
    std::string getChunk(unsigned int index) const;
    virtual unsigned int bitsPerChunk() const;
    std::string getName() const;
};

#endif // BCD_H
