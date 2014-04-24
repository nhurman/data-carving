#include "algorithms/similarities.h"
#include <iostream>

Similarities::Similarities(std::vector<Dump> dumps, int minSize) : m_dumps(dumps)
{
    for(unsigned int i = 0; i < m_dumps.size(); i++)
    {
        std::list< SIM_TYPE > simi;
        for(unsigned int j = i+1; j < m_dumps.size(); j++)
        {
            std::list<std::pair<int, int> > l = BitString::similarities(*m_dumps[i].getBitString(), *m_dumps[j].getBitString(), minSize);
            addSimilarities(&simi, &l, i, j);
        }
        addSimList(&simi);
    }
    //std::cout << toString() << std::endl;
}

int Similarities::getDumpId(Dump d)
{
    for(unsigned int i = 0; i < m_dumps.size(); i++)
    {
        if(d.getFileName() == m_dumps[i].getFileName())
            return i;
    }
    return -1;
}

int Similarities::getDumpCount()
{
    return m_dumps.size();
}

std::list< SIM_TYPE >* Similarities::getList()
{
    return &m_similarities;
}

void Similarities::addSimilarities(std::list<SIM_TYPE>* sim1, std::list<std::pair<int, int> >* sim2, int d1, int d2)
{
    std::list< SIM_TYPE >::iterator j = sim1->begin();
    for (std::list<std::pair<int,int> >::iterator i = sim2->begin(); i != sim2->end(); i++ )
    {
        if(j == sim1->end())
        {
            std::list<int> l;
            l.push_back(d1);
            l.push_back(d2);
            sim1->push_back(SIM_TYPE (*i, l) );
        }
        else
        {
            if(j->first.second > i->first) //let [a;b] e sim1, [x,y] e sim2. if(b > x)
            {
                std::list<int> l;
                l.push_back(d1);
                l.push_back(d2);
                if(j->first.first < i->second) //if(a < y)
                {
                    //[a,b] inter [x,y] != NULL
                    std::list< SIM_TYPE > newSim = uniteSim(*j, SIM_TYPE (*i, l));
                    j = sim1->erase(j);
                    sim1->insert(j, newSim.begin(), newSim.end() );
                }
                else
                {
                    //we add the new similarity as it doesn't collide with any existing ones
                    sim1->insert(j, SIM_TYPE (*i, l) );
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
}

void Similarities::addSimList (std::list< SIM_TYPE >* list)
{
    std::list< SIM_TYPE >::iterator j = m_similarities.begin();
    for (std::list< SIM_TYPE >::iterator i = list->begin(); i != list->end(); i++ )
    {
        if(j == m_similarities.end())
        {
            m_similarities.push_back(*i);
        }
        else
        {
            if(j->first.second > i->first.first) //let [a;b] e sim1, [x,y] e sim2. if(b > x)
            {
                if(j->first.first < i->first.second) //if(a < y)
                {
                    //[a,b] inter [x,y] != NULL
                    std::list< SIM_TYPE > newSim = intersectSim(*j, *i);
                    j = m_similarities.erase(j);
                    m_similarities.insert(j, newSim.begin(), newSim.end() );
                }
                else
                {
                    //we add the new similarity as it doesn't collide with any existing ones
                    m_similarities.insert(j, *i);
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
}

std::list< SIM_TYPE > Similarities::uniteSim(SIM_TYPE s1, SIM_TYPE s2, int minSize)
{
    std::list< SIM_TYPE > l;
    std::list<int> s1secondUs2second = s1.second; //union of s1.second and s2.second
    for (std::list<int>::iterator i = s2.second.begin(); i != s2.second.end(); i++ )
        s1secondUs2second.push_back(*i);
    //removing duplicates
    s1secondUs2second.sort();
    s1secondUs2second.unique();

    if(s1.first.first < s2.first.first)
    {
        if(s1.first.second > s2.first.second) //s2 C s1
        {
            if(s2.first.first - s1.first.first >= minSize)
                l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.first, s2.first.first-1), s1.second));

            l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.first, s2.first.second), s1secondUs2second));

            if(s1.first.second - s2.first.second >= minSize)
                l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.second+1, s1.first.second), s1.second));
        }
        else //s1.end e s2 && s2.begin e s1
        {
            if(s2.first.first - s1.first.first >= minSize)
                l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.first, s2.first.first-1), s1.second));

            if(s1.first.second - s2.first.first +1 >= minSize)
                l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.first, s1.first.second), s1secondUs2second));

            if(s2.first.second - s1.first.second >= minSize)
                l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.second+1, s2.first.second), s2.second));
        }
    }
    else
    {
        if(s1.first.second < s2.first.second) //s1 C s2
        {
            if(s1.first.first - s2.first.first >= minSize)
                l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.first, s1.first.first-1), s2.second));

            l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.first, s1.first.second), s1secondUs2second));

            if(s2.first.second - s1.first.second >= minSize)
                l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.second+1, s2.first.second), s2.second));
        }
        else //s2.end e s1 && s1.begin e s2
        {
            if(s1.first.first - s2.first.first >= minSize)
                l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.first, s1.first.first-1), s2.second));

            if(s2.first.second - s1.first.first +1 >= minSize)
                l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.first, s2.first.second), s1secondUs2second));

            if(s1.first.second - s2.first.second >= minSize)
                l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.second+1, s1.first.second), s1.second));
        }
    }
    return l;
}

std::list< SIM_TYPE > Similarities::intersectSim(SIM_TYPE s1, SIM_TYPE s2, int minSize)
{
    std::list< SIM_TYPE > l;
    std::list<int> maxSecond; //max of s1.second and s2.second (in terms of nb of elts)
    bool is1greater;
    if(s1.second.size() < s2.second.size())
    {
        maxSecond = s2.second;
        is1greater = false;
    }
    else
    {
        maxSecond = s1.second;
        is1greater = true;
    }

    if(s1.first.first < s2.first.first)
    {
        if(s1.first.second > s2.first.second) //s2 C s1
        {
            if(is1greater)//if s1 is greater and s2 C s1 we keep s1
            {
                l.push_back(s1);
            }
            else
            {
                if(s2.first.first - s1.first.first >= minSize)
                    l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.first, s2.first.first-1), s1.second));

                l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.first, s2.first.second), maxSecond));

                if(s1.first.second - s2.first.second >= minSize)
                    l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.second+1, s1.first.second), s1.second));
            }
        }
        else //s1.end e s2 && s2.begin e s1
        {
            if(s2.first.first - s1.first.first >= minSize)
                l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.first, s2.first.first-1), s1.second));

            if(s1.first.second - s2.first.first +1 >= minSize)
                l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.first, s1.first.second), maxSecond));

            if(s2.first.second - s1.first.second >= minSize)
                l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.second+1, s2.first.second), s2.second));
        }
    }
    else
    {
        if(s1.first.second < s2.first.second) //s1 C s2
        {
            if(!is1greater)//if s2 is greater and s1 C s2 we keep s2
            {
                l.push_back(s2);
            }
            else
            {
                if(s1.first.first - s2.first.first >= minSize)
                    l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.first, s1.first.first-1), s2.second));

                l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.first, s1.first.second), maxSecond));

                if(s2.first.second - s1.first.second >= minSize)
                    l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.second+1, s2.first.second), s2.second));
            }
        }
        else //s2.end e s1 && s1.begin e s2
        {
            if(s1.first.first - s2.first.first >= minSize)
                l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.first, s1.first.first-1), s2.second));

            if(s2.first.second - s1.first.first +1 >= minSize)
                l.push_back(SIM_TYPE (std::pair<int,int>(s1.first.first, s2.first.second), maxSecond));

            if(s1.first.second - s2.first.second >= minSize)
                l.push_back(SIM_TYPE (std::pair<int,int>(s2.first.second+1, s1.first.second), s1.second));
        }
    }
    return l;
}

std::string Similarities::toString() const
{
    std::string s = "Similarities :\n";
    for(SIM_TYPE sim: m_similarities)
    {
        char c[8];
        s += "[";
        s += itoa(sim.first.first, c, 10);
        s += " ; ";
        s += itoa(sim.first.second, c, 10);
        s += "] :";
        for(int i: sim.second)
        {
            s += " ";
            s += itoa(i, c, 10);
        }
        s += "\n";
    }
    return s;
}

void Similarities::test()
{
    //std::vector<Dump> v;
    //v.push_back(Dump ("F:\\Gabriel\\Programmation\\Data Carving\\Utils\\TestFiles\\MultiSim\\1.txt"));
    //v.push_back(Dump ("F:\\Gabriel\\Programmation\\Data Carving\\Utils\\TestFiles\\MultiSim\\2.txt"));
    //v.push_back(Dump ("F:\\Gabriel\\Programmation\\Data Carving\\Utils\\TestFiles\\MultiSim\\3.txt"));
    //Similarities s(v);
}

int Similarities::minStringSize(std::list<int> sizes)
{
    int minSize = 0; //minimum size
    for(std::list<int>::iterator i = sizes.begin(); i != sizes.end(); i++)
    {
        minSize = std::min(minSize, *i);
    }
    int nbDumps = sizes.size();
    int t = minSize*nbDumps*(nbDumps-1)/2;
    return 4.29 + LOG2(t) + .99; //+.99 : cheap way to round up the result
}
