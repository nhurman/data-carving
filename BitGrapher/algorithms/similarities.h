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
    std::string toString() const;

    //probabilities
    static int minStringSize(std::list<int> sizes); //give it the dump sizes

    static void test();

private:
    std::vector<Dump> m_dumps;
    std::list< Similarity > m_similarities;

    void addSimilarities(std::list< Similarity >* sim1, std::list<std::pair<int, int> >* sim2, int d1, int d2);
    void addSimList (std::list< Similarity >* list);

    static std::list< Similarity > uniteSim(Similarity s1, Similarity s2, int minSize = 1); //only call if there is an intersection
    static std::list< Similarity > intersectSim(Similarity s1, Similarity s2, int minSize = 1); //only call if there is an intersection

};

#endif // SIMILARITIES_H
