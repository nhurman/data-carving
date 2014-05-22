#ifndef DUMPSET_H
#define DUMPSET_H

#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Dump.h"
#include "Exception.h"
class DumpSet
{
public:
    DumpSet(std::string filePath = "");
    ~DumpSet();

    Dump const* add(std::string filePath, InputFormat format = RAW);
    void remove(std::string filePath);
    bool save();
    bool save(std::string filePath);

    std::string fileName() const;
    std::string filePath() const;
    bool modified() const;
    size_t size() const;

    Dump const* find(std::string name) const;
    std::map<std::string, Dump const*> dumps() const;
    std::vector<std::string> getDumpNames() const;

private:
    std::map<std::string, Dump const*> m_dumps;
    std::string m_filePath;
    bool m_modified;

    std::string toAbsolute(const std::string relativePath) const;
    std::string toRelative(const std::string absolutePath) const;
};

#endif // DUMPSET_H
