#ifndef SIMILARITIES_H
#define SIMILARITIES_H

#include "dumpset.h"
#define SIM_TYPE std::pair<std::pair<int, int>, std::list<int> >

class Similarities
{
public:
    Similarities(std::vector<Dump> dumps);

    static void test();

private:
    std::vector<Dump> m_dumps;
    std::list< SIM_TYPE > m_similarities;

    void addSimilarities(std::list< SIM_TYPE >* sim1, std::list<std::pair<int, int> >* sim2, int d1, int d2);
    void addSimList (std::list< SIM_TYPE >* list);

    static std::list< SIM_TYPE > uniteSim(SIM_TYPE s1, SIM_TYPE s2); //only call if there is an intersection
    static std::list< SIM_TYPE > intersectSim(SIM_TYPE s1, SIM_TYPE s2); //only call if there is an intersection
};

#endif // SIMILARITIES_H
