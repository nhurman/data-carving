#ifndef DUMPSET_H
#define DUMPSET_H

#include "dump.h"

class DumpSet
{
public:
    DumpSet();
    //loads a dump to the dumpSet
    void addDump(std::string fileName);
    //finds a dump in the dumpSet. Returns null if not found
    Dump* find(std::string name);
    //removes a dump from the set
    void remove(std::string name);

private:
    std::map<std::string, Dump> m_dumps;
};

#endif // DUMPSET_H
