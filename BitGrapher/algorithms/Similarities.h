#ifndef SIMILARITIES_H
#define SIMILARITIES_H

#include "core/DumpSet.h"

#define LOG2(x) std::log(x)/log(2)

typedef std::pair<std::pair<int, int>, std::list<int> > Similarity;

/// \class Similarities
///
/// \brief Class used to process and save the results of the Similarities algorithm.
///
/// \author Gabriel Prevosto
///
/// \date 24/05/2014

class Similarities
{
public:

    /// \brief A constructor for Similarities.
    /// \param dumps The dumps to compare using the algorithm.
    /// \param minSize The minimum size for the similarities.
    /// \note The algoritm is run in this method.
    Similarities(std::vector<Dump const*> const dumps, int const minSize = 1);

    /// \brief Looks for the given Dump and returns its ID.
    /// \param d The dump to look for.
    /// \return The ID of the given Dump, or -1 if it was not found.
    /// \note Two Dumps are considered equal if they have the same file path.
    int getDumpId(Dump const d) const; //returns the Id of the dump or -1 if not found. Equality tested on dump names

    /// \brief Returns the number of Dumps processed.
    /// \return The number of Dumps processed.
    int getDumpCount() const;

    /// \brief Getter for m_similarities.
    /// \return The list of the similarities found by the algorithm.
    /// \note For an easier usage of this class, use getSimilarities instead when possible.
    std::list< Similarity > *getList();

    /// \brief Reorganizes the similarities to sort them on whether they consern a given Dump or not.
    /// \param dumpId The ID of the Dump to consider.
    /// \param charSize the size of a character in the current Encoding.
    /// \return The list of similarities for a given dump.
    /// The float represents the importance of the similarity (close to 1 : almost every Dump has it),
    /// and if it concerns the given DUmp or not (positive : it concerne the given Dump).
    /// The int represents the end of the similarity (-1 represents the end of the Dump.
    std::list<std::pair<float, int> > *getSimilarities(int const dumpId, int const charSize = 1);

    /// \brief Reorganizes the similarities to sort them on whether they consern a given Dump or not.
    /// \param d The Dump to consider.
    /// \param charSize the size of a character in the current Encoding.
    /// \return The list of similarities for a given dump.
    /// The float represents the importance of the similarity (close to 1 : almost every Dump has it),
    /// and if it concerns the given DUmp or not (positive : it concerne the given Dump).
    /// The int represents the end of the similarity (-1 represents the end of the Dump.
    std::list<std::pair<float, int> > *getSimilarities(Dump const d, int const charSize = 1);

    /// \brief Gives a representation of the results of the algorithm in the form of a string.
    /// \return The representation of the results of the algorithm.
    std::string toString() const;

    //probabilities
    /// \brief Processes the preferred minimum string size.
    /// \param sizes The Dump's sizes.
    /// \return The preferred minimum string size.
    static int minStringSize(std::list<int> sizes);

    /// \brief Convert bit coordinates to string coordinates in an Encoding.
    /// \param c The coordinates (in bits) to be converted.
    /// \param charSize The size  of the characters (in bits) from the Encoding to use.
    /// \param roundUp Whether or not the result should be rounded up when in the middle of a character.
    /// \return The converted coordinates.
    static int convertCoords(int const c, int const charSize, bool const roundUp = false);

    //static void test();

private:
    std::vector<const Dump *> m_dumps; ///< The dumps to compare using the algorithm.
    std::list< Similarity > m_similarities; ///< The list of the similarities found by the algorithm.

    /// \brief Adds the similarities from sim2 to sim1.
    /// \param sim1 A list of similartites implying two or more dumps.
    /// \param sim2 The comparison between d1 annd d2.
    /// \param d1 The index of one of the dummps compared in sim2.
    /// \param d2 The index of one of the dummps compared in sim2.
    void addSimilarities(std::list< Similarity >* sim1, std::list<std::pair<int, int> >* sim2, int const d1, int const d2);

    /// \brief Adds a list of similarities to m_similarities.
    /// \param list The list of similarities to add.
    void addSimList (std::list< Similarity >* list);

    /// \brief Processes the similarities between two Dumps.
    /// \param b1 One of the Dumps to compare.
    /// \param b2 One of the Dumps to compare.
    /// \param minSize The minimum size for the similarities.
    /// \return The similarities between b1 and b2.
    static std::list<std::pair<int,int> > compare2Dumps(BitString const b1, BitString const b2, int minSize = 1);

    /// \brief Processes the similarities corresponding to the union of s1 and s2
    /// (when s1 and s2 overlap, creates a new similarities with all of their related Dumps)
    /// \param s1 A similarity to process.
    /// \param s2 A similarity to process.
    /// \param minSize The minimum size for the similarities.
    /// \return The similarities corresponding to the union of s1 and s2
    /// \note Only call if s1 and s2 overlap.
    static std::list< Similarity > uniteSim(Similarity s1, Similarity s2, int const minSize = 1);

    /// \brief Processes the similarities corresponding to the intersection of s1 and s2
    /// (when s1 and s2 overlap, creates a new similarities with the Dumps common to s1 and s2)
    /// \param s1 A similarity to process.
    /// \param s2 A similarity to process.
    /// \param minSize The minimum size for the similarities.
    /// \return The similarities corresponding to the intersection of s1 and s2
    /// \note Only call if s1 and s2 overlap.
    static std::list< Similarity > intersectSim(Similarity s1, Similarity s2, int const minSize = 1);

    /// \brief Adds the pair (color, endIndex) to the list while updating oldColor.
    /// \param list The list to which the pair will be added.
    /// \param color The color to add to the pair.
    /// \param oldColor This color will be made identical to color at the end of this function.
    /// \param endIndex The index to add to the pair.
    /// \note Used for getSimilarities.
    static void addColor(std::list<std::pair<float, int> >* list, float const color, float &oldColor, int const endIndex);

};

#endif // SIMILARITIES_H
