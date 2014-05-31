#ifndef DUMPSET_H
#define DUMPSET_H

#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Dump.h"
#include "Exception.h"

/// \class DumpSet
///
/// \brief Modelizes a dump set.
///
/// \author Gabriel Prevosto
/// \author Nicolas Hurman
///
/// \date 23/05/2014

class DumpSet
{
public:

    /// \brief Makes a DumpSet from its file path.
    /// \param filePath The DumpSet's filepath. Leave empty for a new DumpSet.
    DumpSet(std::string filePath = "");

    /// \brief The DumpSet's destructor.
    ~DumpSet();

    /// \brief Adds a Dump to the DumpSet.
    /// \param filePath The Dump's file path.
    /// \param format The input format used in the file. RAW by default.
    /// \return The Dump made from the file path.
    Dump const* add(std::string filePath, InputFormat format = RAW);

    /// \brief Removes a Dump from the DumpSet.
    /// \param filePath The Dump's file path.
    void remove(std::string filePath);

    /// \brief Saves the DumpSet to its file path.
    /// \return Set to true if the save was a success.
    bool save();

    /// \brief Saves the DumpSet to a new file path.
    /// \param filePathThe DumpSet's new file path.
    /// \return Set to true if the save was a success.
    /// \note  The given filepath will replace the DumpSet's old file path afterwards.
    bool save(std::string filePath);

    /// \brief Gets the name of the DumpSet from its file path.
    /// \return The DumpSet's file name.
    std::string fileName() const;

    /// \brief Getter for m_filePath.
    /// \return The DumpSet's file path.
    std::string filePath() const;

    /// \brief Getter for m_modified
    /// \return Whether or not the DumpSet has been modified since it was last saved.
    bool modified() const;

    /// \brief Returns the size of the DumpSet.
    /// \return The number of Dumps currently in the DumpSet.
    size_t size() const;

    /// \brief Finds a Dump by its name.
    /// \param name The name of the Dump to look for.
    Dump const* find(std::string name) const;

    /// \brief Getter for m_dumps.
    /// \return The Dumps contained in the DumpSet, sorted by name.
    std::map<std::string, Dump const*> dumps() const;

    /// \brief Gets the list of all the Dump's names.
    /// \return The list of all the Dump's names.
    std::vector<std::string> getDumpNames() const;

    /// \brief Gets the list of all the Dumps.
    /// \return The list of all the Dumps.
    std::vector<const Dump *> getDumpList() const;

private:
    std::map<std::string, Dump const*> m_dumps; ///< The Dumps contained in the DumpSet, sorted by name.
    std::string m_filePath; ///< The DumpSet's file path.
    bool m_modified; ///< The DumpSet's format.

    /// \brief Translates a relative file path into an absolute one.
    /// \param relativePath The file path to translate.
    /// \return The translated file path.
    std::string toAbsolute(const std::string relativePath) const;

    /// \brief Translates a absolute file path into an relative one.
    /// \param absolutePath The file path to translate.
    /// \return The translated file path.
    std::string toRelative(const std::string absolutePath) const;
};

#endif // DUMPSET_H
