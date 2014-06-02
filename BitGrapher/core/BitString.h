#ifndef BITSTRING_H
#define BITSTRING_H

#include <string>
#include <list>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <fstream>
#include <iostream>

#include "Exception.h"
#include "algorithms/DotPlotPattern.h"
#include "algorithms/Diagonal.h"

enum InputFormat {HEXADECIMAL, BINARY, RAW};

/*!
 * \class BitString
 * \brief Represents a bit string
 *
 * \author Nicolas Hurman
 * \author Gabriel Prevosto
 * \date 20/03/2014
 */
class BitString
{
public:
    /*!
     * \brief Constructor, with an optional size
     * \param size Bitstring initial size
     */
    BitString(size_t size = 0);

    /*!
     * \brief Copy constructor
     * \param other BitString to copy
     */
    BitString(BitString const& other);

    /*!
     * \brief Affectation operator
     * \param size Bitstring to copy
     */
    BitString& operator=(BitString const& other);

    /*!
     * \brief Creates a BitString from a binary string (with ASCII 0 and 1s)
     * \param str Input string, eg "01010100"
     * \return New BitString
     */
    static BitString fromBin(std::string str);

    /*!
     * \brief Creates a BitString from a hex string (with ASCII 0-1 and A-F)
     * \param str Input string, eg "DEADBEEF"
     * \return New BitString
     */
    static BitString fromHex(std::string str);

    /*!
     * \brief Creates a BitString from raw data
     * \param str Input string. Can be anything, the ASCII codes will be used as binary values
     * \return New BitString
     */
    static BitString fromRaw(std::string str);

    /*!
     * \brief Creates a BitString with the given format
     * \param format Input format
     * \return New BitString
     */
    static BitString makeBitString(std::string str, InputFormat format = HEXADECIMAL);

    /*!
     * \brief Destructor
     */
    ~BitString();

    /*!
     * \brief Return this BitString's size in bits
     * \return Size
     */
    size_t size() const;

    /*!
     * \brief Returns one bit
     * \param index Bit index
     * \return bit
     */
    bool operator[](unsigned int index) const;

    /*!
     * \brief Sets one bit
     * \param index Bit index
     * \param value Buit value
     * \return New value
     */
    bool set(unsigned int index, bool value);

    /*!
     * \brief Return this BitString's size in bits
     * \return Size
     */
    int getSize() const;

    // Bitwise operators

    /*!
     * \brief Bitwise AND
     * \param other Second BitString to perform the operation with
     * \return New BitString
     */
    BitString operator&(BitString const& other);

    /*!
     * \brief Bitwise OR
     * \param other Second BitString to perform the operation with
     * \return New BitString
     */
    BitString operator|(BitString const& other);

    /*!
     * \brief Bitwise XOR
     * \param other Second BitString to perform the operation with
     * \return New BitString
     */
    BitString operator^(BitString const& other);

    /*!
     * \brief Compares two BitString instances
     * \param other Other BitString
     * \return True if they are the same
     */
    bool operator==(BitString const& other) const;

    /*!
     * \brief Compares two BitString instances
     * \param other Other BitString
     * \return False if they are the same
     */
    bool operator!=(BitString const& other) const;

    /*!
     * \brief Extracts a consequetive array of bits from this BitString
     * \param start Start index
     * \param size Substring length
     * \return Substring
     */
    BitString substring(unsigned int start, size_t size) const;

    /*!
     * \brief Checks if another BitString is contained in this one
     * \param bs Other BitString
     * \return True if bs is contained in the current BitString
     */
    bool contains(BitString const& bs) const;

    /*!
     * \brief Returns a text representation of this BitString using ASCII 0 and 1s
     * \return Text representation eg "1010100"
     */
    std::string toString() const;


    /*!
     * \brief Guesses the format of a file
     * \param fileName File name
     * \return Guessed format
     */
    static InputFormat guessFileInputFormat(std::string fileName);

    /*!
     * \brief Guesses the format of a string
     * \param text String
     * \return Guessed format
     */
    static InputFormat guessTextInputFormat(std::string text);

    /*!
     * \brief Converts a text reprensentation of a format into the matching constant
     * \param formatStr Format string eg "HEXADECIMAL"
     * \return Format constant eg HEXADECIMAL
     */
    static InputFormat stringToFormat(std::string formatStr);

    /*!
     * \brief Converts the format constant into its text representation
     * \param formatStr Format HEXADECIMAL
     * \return Format string eg "HEXADECIMAL"
     */
    static std::string formatToString(InputFormat format);


    /// \brief Dot Plot pattern between 2 dump.
    /// \param dump The dump to compare to.
    /// \return A list of the calculated diagonals.
    std::list<Diagonal> dotPlotPattern(const BitString *dump, unsigned int minDiagSize) const;

    /// \brief Dot Plot pattern on one dump.
    /// \return A list of the calculated diagonals.
    /// \note This is faster than using the 2 dump method.
    std::list<Diagonal> dotPlotPattern(unsigned int minDiagSize) const;

private:
    size_t m_size;
    char*  m_bytes;
};

#endif // BITSTRING_H
