#ifndef SIMILARITIES_H
#define SIMILARITIES_H

#include "dumpset.h"
#define SIM_TYPE std::pair<std::pair<int, int>, std::list<int> >

class Similarities
{
public:
    Similarities(DumpSet* ds, std::vector<Dump> dumps);

private:
    DumpSet* m_dumpSet;
    std::vector<Dump> m_dumps;
    std::list< SIM_TYPE > m_similarities;

    void addSimilarities(std::list<std::pair<int, int> > sim, int d1, int d2);
    std::list< SIM_TYPE > intersectSim(SIM_TYPE s1, SIM_TYPE s2); //only call if there is an intersection
};

#endif // SIMILARITIES_H
