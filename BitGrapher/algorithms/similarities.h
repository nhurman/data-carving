#ifndef SIMILARITIES_H
#define SIMILARITIES_H

#include "core/dumpset.h"

#define LOG2(x) std::log(x)/log(2)

typedef std::pair<std::pair<int, int>, std::list<int> > Similarity;

class Similarities
{
public:
    Similarities(std::vector<Dump> dumps, int minSize = MIN_SIM_SIZE);
    int getDumpId(Dump d); //returns the Id of the dump or -1 if not found. Equality tested on dump names
    int getDumpCount();
    std::list< Similarity > *getList();
    std::list<std::pair<float, int> > *getSimilarities(int dumpId, int charSize = 1); //returns the list similarities for a given dump. The float is the color (-1 : blue, 0 : red, 1 : green), the int the end of the similarity (-1 for end of string)
    std::list<std::pair<float, int> > *getSimilarities(Dump d, int charSize = 1);
    std::string toString() const;

    //probabilities
    static int minStringSize(std::list<int> sizes); //give it the dump sizes
    static int convertCoords(int c, int charSize, bool roundUp = false);

    static void test();

private:
    std::vector<Dump> m_dumps;
    std::list< Similarity > m_similarities;

    void addSimilarities(std::list< Similarity >* sim1, std::list<std::pair<int, int> >* sim2, int d1, int d2);
    void addSimList (std::list< Similarity >* list);

    static std::list< Similarity > uniteSim(Similarity s1, Similarity s2, int minSize = 1); //only call if there is an intersection
    static std::list< Similarity > intersectSim(Similarity s1, Similarity s2, int minSize = 1); //only call if there is an intersection
    static void addColor(std::list<std::pair<float, int> >* list, float color, float &oldColor, int endIndex);

};

#endif // SIMILARITIES_H
