#ifndef DUMP_H
#define DUMP_H

#include <string>
#include <iostream>
#include <fstream>

#include "Exception.h"
#include "BitString.h"

/// \class Dump
///
/// \brief Modelizes a dump.
///
/// \author Gabriel Prevosto
/// \author Nicolas Hurman
///
/// \date 23/05/2014

class Dump
{
public:

    /// \brief Makes a Dump from a file.
    /// \param filePath The path to the file.
    /// \param format The input format used in the file. RAW by default.
    Dump(std::string const& filePath, InputFormat format = RAW);

    /// \brief Makes a copy of a Dump.
    /// \param other the Dump to copy.
    Dump(Dump const& other);

    /// \brief Getter for m_bitString.
    /// \return The Dump's bitstring.
    BitString const* bitString() const;

    /// \brief Getter for m_filePath.
    /// \return The Dump's file path.
    std::string filePath() const;

    /// \brief Gets the name of the Dump from its file path.
    /// \return The Dump's file name.
    std::string fileName() const;

    /// \brief Getter for m_format.
    /// \return The Dump's format.
    InputFormat getFormat() const;

    /// \brief Retrieves the Dump's size from its BitString.
    /// \return The Dump's size in bits.
    int getSize() const;

private:
    BitString m_bitString; ///< The Dump's BitString.
    std::string m_filePath; ///< The Dump's file path.
    InputFormat m_format; ///< The Dump's format.
};

#endif // DUMP_H
