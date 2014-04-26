#include "DumpSet.h"
#include "Exception.h"
#include <fstream>

DumpSet::DumpSet(std::string filePath) : m_filePath(filePath), m_modified(false)
{
    if (filePath.size() > 0) { // existing dump
        std::ifstream f;
        f.open(filePath.c_str());
        if (f.is_open()) {
            m_modified = false;

            std::string name;
            std::string formatStr;

            while(std::getline(f, name, ';')){
                std::cout << "Name : " << name << std::endl;
                std::getline(f, formatStr);
                std::cout << "Format : " << formatStr << std::endl;
                add(name, BitString::stringToFormat(formatStr));
            }
        }
        else {
            throw IOException("Could not open dump set " + filePath);
        }
    }
}

DumpSet::~DumpSet()
{
    for (auto i: m_dumps) {
        delete i.second;
    }
}

Dump const* DumpSet::add(std::string filePath, InputFormat format)
{
    Dump* d = new Dump(filePath, format);
    m_dumps.insert(std::make_pair(filePath, d));
    m_modified = true;
    return d;
}

void DumpSet::remove(std::string filePath)
{
    delete m_dumps[filePath];
    m_dumps.erase(filePath);
    m_modified = true;
}

bool DumpSet::save()
{
    std::ofstream file;
    file.open(m_filePath.c_str());
    if (!file.is_open()) {
        return false;
    }

    for (std::map<std::string, Dump const*>::iterator i = m_dumps.begin(); i != m_dumps.end(); i++) {
        file << i->second->filePath() << ";" << BitString::formatToString(i->second->getFormat()) << std::endl;
    }

    file.close();
    m_modified = false;

    return true;
}

bool DumpSet::save(std::string filePath)
{
    m_filePath = filePath;
    return save();
}

std::string DumpSet::fileName() const
{
    size_t pos = m_filePath.find_last_of('/');
    if (std::string::npos == pos) {
        return m_filePath;
    }

    return m_filePath.substr(pos + 1);
}

std::string DumpSet::filePath() const
{
    return m_filePath;
}

bool DumpSet::modified() const
{
    return m_modified;
}

size_t DumpSet::size() const
{
    return m_dumps.size();
}

Dump const* DumpSet::find(std::string filePath) const
{
    return m_dumps.at(filePath);
}

std::map<std::string, Dump const*> DumpSet::dumps() const
{
    return m_dumps;
}

