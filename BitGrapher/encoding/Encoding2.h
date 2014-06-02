#ifndef ENCODING2_H
#define ENCODING2_H

#include "core/BitString.h"

/*!
 * \class Encoding2
 * \brief Represents an encoding. Abstract class, has to be extended.
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
class Encoding2
{
public:
    /*!
     * \brief Constructor
     */
    Encoding2();

    /*!
     * \brief Destructor
     */
    virtual ~Encoding2();

    /*!
     * \brief Change the decoding offset
     * \param offset Offset, in bits, to start the decoding from
     */
    void setGlobalOffset(unsigned int offset);

    /*!
     * \brief Set the BitString to get data from
     * \param bitString BitString
     */
    void setBitString(BitString const* bitString);

    /*!
     * \brief Get the amount of chunks that can be extracted from the current BitString
     * \return Chunks number
     */
    unsigned int countChunks() const;

    /*!
     * \brief Decode a chunk of data
     * \param index Chunk index
     * \return Decoded data
     */
    virtual std::string getChunk(unsigned int index) const = 0;

    /*!
     * \brief Decode a sequence of bytes
     * \param start Start index, in bits
     * \param length Amount of bits to decode
     */
    std::string decode(unsigned int start, unsigned int length);

    /*!
     * \brief Gets the amount of bits that are consumed per chunk
     * \return Bits per chunk
     */
    virtual unsigned int bitsPerChunk() const = 0;

    /*!
     * \brief Gets this encoding's name in ASCII
     * \return Current encoding name
     */
    virtual std::string getName() const = 0;

protected:
    BitString const* m_bitString;
    unsigned int m_globalOffset;
};

#endif // ENCODING2_H
