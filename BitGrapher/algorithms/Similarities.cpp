#include "algorithms/Similarities.h"
#include <iostream>
#include <QDebug>

Similarities::Similarities(const std::vector<const Dump *> dumps, int offset, const int minSize) : m_dumps(dumps)
{
    m_minSize = minSize;
    for(unsigned int i = 0; i < m_dumps.size(); i++)
    {
        std::list< Similarity > simi;
        for(unsigned int j = i+1; j < m_dumps.size(); j++)
        {
            int size1 = (*m_dumps[i]->bitString()).size() - offset;
            int size2 = (*m_dumps[j]->bitString()).size() - offset;

            std::list<std::pair<int, int> > l = compare2Dumps(
                (*m_dumps[i]->bitString()).substring(offset, size1),
                (*m_dumps[j]->bitString()).substring(offset, size2),
            minSize);
            addSimilarities(&simi, &l, i, j);
        }
        addSimList(&simi);
    }
}

int Similarities::getDumpId(const Dump d) const
{
    for(unsigned int i = 0; i < m_dumps.size(); i++)
    {
        if(d.filePath() == m_dumps[i]->filePath())
            return i;
    }
    return -1;
}

int Similarities::getDumpCount() const
{
    return m_dumps.size();
}

std::list< Similarity >* Similarities::getList()
{
    return &m_similarities;
}

std::list<std::pair<float, int> > * Similarities::getSimilarities(const Dump d, const int charSize)
{
    return getSimilarities(getDumpId(d), charSize);
}

std::list< std::pair<float, int> >* Similarities::getSimilarities(const int dumpId, const int charSize)
{
    std::list< std::pair<float, int> >* sims = new std::list< std::pair<float, int> >();
    int pos = 0;
    float oldColor = 0;
    float currColor = 0;
    for (std::list< Similarity >::iterator i = m_similarities.begin(); i != m_similarities.end() /*&& pos != -1*/; i++ )
    {
        if(m_dumps[dumpId]->getSize() <= i->first.second) //if we arrived at the end of the dump
        {
            if(m_dumps[dumpId]->getSize() > i->first.first) //if the beginning of the next similarity is not too far
            {
                //last similarity
                float ratio = (float) i->second.size()/getDumpCount();
                if(std::find(i->second.begin(), i->second.end(), dumpId) != i->second.end()) //the similarity concerns the selected dump
                    currColor = ratio;
                else
                    currColor = -ratio;

                pos = -1; //going until end of dump

                addColor(sims, currColor, oldColor, pos);

                oldColor = currColor;
            }

            break; //exit loop

        }

        //dissimilarity until next value
        pos = convertCoords(i->first.first, charSize, true) -1; //-1 because it is the beginning fo the next similarity
        if(pos > sims->back().second) //the length can be of 0 or lower due to the encoding
        {
            currColor = 0;

            addColor(sims, currColor, oldColor, pos);
        }

        //similarity
        pos = convertCoords(i->first.second, charSize);
        if(pos > sims->back().second) //the length can be of 0 or lower due to the encoding
        {
            float ratio = (float) i->second.size()/getDumpCount();

            if(std::find(i->second.begin(), i->second.end(), dumpId) != i->second.end()) //the similarity concerns the selected dump
                currColor = ratio;
            else
                currColor = -ratio;

            addColor(sims, currColor, oldColor, pos);
        }

        //Bug Fix
        std::list< Similarity >::iterator j = i; //j = i+1;
        j++;
        pos = sims->back().second + 1;              //We consider the next character, in case it was shared by more than 1 similarity
        if(i->first.second >= j->first.first-1                              //if the next similarity is right next to this one (j is right after i)
                && pos < convertCoords(j->first.first, charSize, true))     // but we are before its converted starting point (pos is before the junction between i and j)
        {
            std::list<int> common = i->second; //will contain the dumps common to the similarities sharing the curent character
            j--; //necessary for the next loop, it starts with j = i
            do
            {
                if(j->first.second >= (j++)->first.first-1) //if the next similarity is right next to this one
                {
                    std::list<int> oldCommon = common;
                    common.clear();
                    std::set_intersection(oldCommon.begin(), oldCommon.end(), j->second.begin(), j->second.end(), std::back_inserter(common)); //common = common inter lj
                }
                else //nothing more to do here
                {
                    common.clear();
                    break;
                }
            }
            while(convertCoords((j)->first.second, charSize) < pos); //we look forward until we find a sim that ends at or beyond pos

            if(common.size() > 1) //if there are at least 2 common elements
            {
                float ratio = (float) common.size()/getDumpCount();

                if(std::find(common.begin(), common.end(), dumpId) != common.end()) //the similarity concerns the selected dump
                    currColor = ratio;
                else
                    currColor = -ratio;

                addColor(sims, currColor, oldColor, pos);
            }
        }
        //Bug Fix End
    }
    if(pos != -1) //if the end was not reached in the loop
    {
        //last dissimilarity
        pos = -1; //text until end
        currColor = 0;

        addColor(sims, currColor, oldColor, pos);
    }

    return sims;
}

void Similarities::addSimilarities(std::list<Similarity>* sim1, std::list<std::pair<int, int> >* sim2, const int d1, const int d2)
{
    std::list< Similarity >::iterator j = sim1->begin();
    for (std::list<std::pair<int,int> >::iterator i = sim2->begin(); i != sim2->end(); i++ )
    {
        if(j == sim1->end())
        {
            std::list<int> l;
            l.push_back(d1);
            l.push_back(d2);
            sim1->push_back(Similarity (*i, l) );
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
                    std::list< Similarity > newSim = uniteSim(*j, Similarity (*i, l));
                    j = sim1->erase(j);
                    sim1->insert(j, newSim.begin(), newSim.end() );
                }
                else
                {
                    //we add the new similarity as it doesn't collide with any existing ones
                    sim1->insert(j, Similarity (*i, l) );
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

void Similarities::addSimList (std::list< Similarity >* list)
{
    std::list< Similarity >::iterator j = m_similarities.begin();
    for (std::list< Similarity >::iterator i = list->begin(); i != list->end(); i++ )
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
                    std::list< Similarity > newSim = intersectSim(*j, *i);
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

std::list< Similarity > Similarities::uniteSim(Similarity s1, Similarity s2, const int minSize)
{
    std::list< Similarity > l;
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
                l.push_back(Similarity (std::pair<int,int>(s1.first.first, s2.first.first-1), s1.second));

            l.push_back(Similarity (std::pair<int,int>(s2.first.first, s2.first.second), s1secondUs2second));

            if(s1.first.second - s2.first.second >= minSize)
                l.push_back(Similarity (std::pair<int,int>(s2.first.second+1, s1.first.second), s1.second));
        }
        else //s1.end e s2 && s2.begin e s1
        {
            if(s2.first.first - s1.first.first >= minSize)
                l.push_back(Similarity (std::pair<int,int>(s1.first.first, s2.first.first-1), s1.second));

            if(s1.first.second - s2.first.first +1 >= minSize)
                l.push_back(Similarity (std::pair<int,int>(s2.first.first, s1.first.second), s1secondUs2second));

            if(s2.first.second - s1.first.second >= minSize)
                l.push_back(Similarity (std::pair<int,int>(s1.first.second+1, s2.first.second), s2.second));
        }
    }
    else
    {
        if(s1.first.second < s2.first.second) //s1 C s2
        {
            if(s1.first.first - s2.first.first >= minSize)
                l.push_back(Similarity (std::pair<int,int>(s2.first.first, s1.first.first-1), s2.second));

            l.push_back(Similarity (std::pair<int,int>(s1.first.first, s1.first.second), s1secondUs2second));

            if(s2.first.second - s1.first.second >= minSize)
                l.push_back(Similarity (std::pair<int,int>(s1.first.second+1, s2.first.second), s2.second));
        }
        else //s2.end e s1 && s1.begin e s2
        {
            if(s1.first.first - s2.first.first >= minSize)
                l.push_back(Similarity (std::pair<int,int>(s2.first.first, s1.first.first-1), s2.second));

            if(s2.first.second - s1.first.first +1 >= minSize)
                l.push_back(Similarity (std::pair<int,int>(s1.first.first, s2.first.second), s1secondUs2second));

            if(s1.first.second - s2.first.second >= minSize)
                l.push_back(Similarity (std::pair<int,int>(s2.first.second+1, s1.first.second), s1.second));
        }
    }
    return l;
}

std::list< Similarity > Similarities::intersectSim(Similarity s1, Similarity s2, const int minSize)
{
    std::list< Similarity > l;
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
                    l.push_back(Similarity (std::pair<int,int>(s1.first.first, s2.first.first-1), s1.second));

                l.push_back(Similarity (std::pair<int,int>(s2.first.first, s2.first.second), maxSecond));

                if(s1.first.second - s2.first.second >= minSize)
                    l.push_back(Similarity (std::pair<int,int>(s2.first.second+1, s1.first.second), s1.second));
            }
        }
        else //s1.end e s2 && s2.begin e s1
        {
            if(s2.first.first - s1.first.first >= minSize)
                l.push_back(Similarity (std::pair<int,int>(s1.first.first, s2.first.first-1), s1.second));

            if(s1.first.second - s2.first.first +1 >= minSize)
                l.push_back(Similarity (std::pair<int,int>(s2.first.first, s1.first.second), maxSecond));

            if(s2.first.second - s1.first.second >= minSize)
                l.push_back(Similarity (std::pair<int,int>(s1.first.second+1, s2.first.second), s2.second));
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
                    l.push_back(Similarity (std::pair<int,int>(s2.first.first, s1.first.first-1), s2.second));

                l.push_back(Similarity (std::pair<int,int>(s1.first.first, s1.first.second), maxSecond));

                if(s2.first.second - s1.first.second >= minSize)
                    l.push_back(Similarity (std::pair<int,int>(s1.first.second+1, s2.first.second), s2.second));
            }
        }
        else //s2.end e s1 && s1.begin e s2
        {
            if(s1.first.first - s2.first.first >= minSize)
                l.push_back(Similarity (std::pair<int,int>(s2.first.first, s1.first.first-1), s2.second));

            if(s2.first.second - s1.first.first +1 >= minSize)
                l.push_back(Similarity (std::pair<int,int>(s1.first.first, s2.first.second), maxSecond));

            if(s1.first.second - s2.first.second >= minSize)
                l.push_back(Similarity (std::pair<int,int>(s2.first.second+1, s1.first.second), s1.second));
        }
    }
    return l;
}

std::string Similarities::toString() const
{
    std::stringstream s;
    s << "Similarities :\n";
    for(Similarity sim: m_similarities)
    {
        s << "[" << sim.first.first << " ; " << sim.first.second << "] :";
        for(int i: sim.second)
        {
            s << " " << i;
        }
        s << "\n";
    }
    return s.str();
}

//void Similarities::test()
//{
//    std::vector<Dump> v;
//    v.push_back(Dump ("F:\\Gabriel\\Programmation\\Data Carving\\Utils\\TestFiles\\MultiSim\\1.txt"));
//    v.push_back(Dump ("F:\\Gabriel\\Programmation\\Data Carving\\Utils\\TestFiles\\MultiSim\\2.txt"));
//    v.push_back(Dump ("F:\\Gabriel\\Programmation\\Data Carving\\Utils\\TestFiles\\MultiSim\\3.txt"));
//    Similarities s(v);
//}

int Similarities::minStringSize(std::list<int> sizes)
{
    if(!sizes.empty())
    {
        std::list<int>::iterator i = sizes.begin();
        int minSize = *i; //minimum size (initialized at first one)
        for(i++; i != sizes.end(); i++)
        {
            minSize = std::min(minSize, *i);
        }
        int nbDumps = sizes.size();
        int t = minSize*nbDumps*(nbDumps-1)/2;
        return 4.29 + LOG2(t) + .99; //+.99 : cheap way to round up the result
    }
    return 1; //default value if empty list
}

int Similarities::convertCoords(const int c, const int charSize, const bool roundUp)
{
    if(charSize == 1)
        return c;

    //else
    int res = c/charSize;

    if(roundUp && c%charSize != 0)
        res ++;
    else if(!roundUp && c%charSize != charSize-1)
        res--;

    return res;
}

void Similarities::addColor(std::list<std::pair<float, int> >* list, const float color, float &oldColor, const int endIndex)
{
    if(color == oldColor)
        list->back().second = endIndex;
    else
        list->push_back(std::pair<float, int>(color, endIndex));

    oldColor = color;
}

std::list<std::pair<int,int> > Similarities::compare2Dumps(const BitString b1, const BitString b2, int minSize)
{
    std::list<std::pair<int,int> > sim;
    int start = -1;
    int min = std::min(b1.size(), b2.size());
    int i;
    for (i = 0; i < min ; i++){
        if(b1[i]==b2[i])
        {
            if(start == -1)
                start = i;
        }
        else
        {
            if(start != -1)
            {
                if(i-start >= minSize)
                {
                    sim.push_back(std::pair<int,int>(start, i-1));
                }
                start = -1;
            }
        }
    }
    if(start != -1) //check for a last similarity at the end
    {
        if(i-start >= minSize)
        {
            sim.push_back(std::pair<int,int>(start, i-1));
        }
    }

    return sim;
}
