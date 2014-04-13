#include "similarities.h"

Similarities::Similarities(DumpSet* ds, std::vector<Dump> dumps) : m_dumpSet(ds), m_dumps(dumps)
{
    for(unsigned int i = 0; i < m_dumps.size(); i++)
    {
        for(unsigned int j = i+1; j < m_dumps.size(); j++)
        {
            std::list<std::pair<int, int> > l = BitString::similarities(*m_dumps[i].getBitString(), *m_dumps[j].getBitString());
            addSimilarities(l, i, j);
        }
    }
}

void Similarities::addSimilarities(std::list<std::pair<int, int> > sim, int d1, int d2)
{
    std::list< SIM_TYPE >::iterator j = m_similarities.begin();
    for (std::list<std::pair<int,int> >::iterator i = sim.begin(); i != sim.end(); i++ )
    {
        if(j->first.second > i->first) //let [a;b] e sim, [x,y] e m_sim. if(b > x)
        {
            std::list<int> l;
            l.push_back(d1);
            l.push_back(d2);
            if(j->first.first < i->second) //if(a < y)
            {
                //[a,b] inter [x,y] != NULL
                std::list< SIM_TYPE > newSim = intersectSim(*j, SIM_TYPE (*i, l));
                j = m_similarities.erase(j);
                m_similarities.insert(j, newSim.begin(), newSim.end() );
            }
            else
            {
                //we add the new similarity as it doesn't collide with any existing ones
                m_similarities.insert(j, SIM_TYPE (*i, l) );
            }
        }
        else
        {
            //we increase j instead of i to catch up with the current similarity
            j++;
            i--;
        }
    }
}

std::list< SIM_TYPE > Similarities::intersectSim(SIM_TYPE s1, SIM_TYPE s2)
{
    std::list< SIM_TYPE > l;
    std::list<int> s1secondUs2second = s1.second; //union of s1.second and s2.second
    for (std::list<int>::iterator i = s2.second.begin(); i != s2.second.end(); i++ )
        s1secondUs2second.push_back(*i);

    if(s1.first.first < s2.first.first)
    {
        if(s1.first.second > s2.first.second) //s2 C s1
        {
            l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.first, s2.first.first), s1.second));
            l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.first, s2.first.second), s1secondUs2second));
            l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.second, s1.first.second), s1.second));
        }
        else //s1.end e s2 && s2.begin e s1
        {
            l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.first, s2.first.first), s1.second));
            l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.first, s1.first.second), s1secondUs2second));
            l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.second, s2.first.second), s2.second));
        }
    }
    else
    {
        if(s1.first.second < s2.first.second) //s1 C s2
        {
            l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.first, s1.first.first), s2.second));
            l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.first, s1.first.second), s1secondUs2second));
            l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.second, s2.first.second), s2.second));
        }
        else //s2.end e s1 && s1.begin e s2
        {
            l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.first, s1.first.first), s2.second));
            l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.first, s2.first.second), s1secondUs2second));
            l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.second, s1.first.second), s1.second));
        }
    }
    return l;
}
