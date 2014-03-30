#include "dumpset.h"

DumpSet::DumpSet()
{
}

void DumpSet::addDump(std::string fileName)
{
    m_dumps[fileName] = Dump(fileName);
}

Dump* DumpSet::find(std::string name)
{
    std::map<std::string, Dump>::iterator i = m_dumps.find(name);
    if( i != m_dumps.end())
    {
        return &(i->second);
    }
    return NULL;
}

void DumpSet::remove(std::string name)
{
    m_dumps.erase(name);
}
