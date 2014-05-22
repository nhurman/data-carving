#include "DumpSet.h"


DumpSet::DumpSet(std::string filePath) : m_filePath(filePath), m_modified(false)
{
    if (filePath.size() > 0) { // existing dump
        std::ifstream f;
        f.open(filePath.c_str());
        if (f.is_open()) {
            //m_modified = false;

            std::string name;
            std::string formatStr;

            while(std::getline(f, name, ';')){
                std::getline(f, formatStr);
                add(toAbsolute(name), BitString::stringToFormat(formatStr));
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
        file << toRelative( i->second->filePath() ) << ";" << BitString::formatToString(i->second->getFormat()) << std::endl;
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


std::vector<std::string> DumpSet::getDumpNames() const
{
    std::vector<std::string> v;
    for(std::map<std::string, Dump const*>::const_iterator it = m_dumps.begin(); it != m_dumps.end(); ++it) {
      v.push_back(it->first);
    }
    return v;
}


std::string DumpSet::toAbsolute(const std::string relativePath) const
{
    char separator = '/';
    if(m_filePath.find('/') == std::string::npos) //if there is no '/' in the dumpset's filepath
        separator = '\\'; //change the separator to '\'

    int nbParent = 0; //nb of times we go back to a parent folder
    std::string absolutePath = m_filePath.substr(0, m_filePath.find_last_of(separator)); //we take back the name of the bitString
    std::istringstream relativeSS( relativePath );
    std::string token;
    while( std::getline( relativeSS, token, separator ) && token == ".." )
    {
        nbParent++;
    }
    for( ; nbParent > 0 ; nbParent-- )
    {
        absolutePath = absolutePath.substr(0, absolutePath.find_last_of(separator)); //we go backwards as many times as the nuber of ..
    }
    absolutePath = absolutePath.append(separator + token); //last thing we read, and it was not "..", remember ?

    if( std::getline( relativeSS, token ) )
        absolutePath = absolutePath.append(separator + token); //we read until the end of the path, and we add it all no the result

    return absolutePath;
}

std::string DumpSet::toRelative(const std::string absolutePath) const
{
    char separator = '/';
    if(m_filePath.find('/') == std::string::npos) //if there is no '/' in the dumpset's filepath
        separator = '\\'; //change the separator to '\'

    std::string relativepPath = "";
    std::istringstream dumpSS( absolutePath );
    std::istringstream dumpSetSS( m_filePath );
    std::string dumpToken;
    std::string dumpSetToken;
    while( std::getline( dumpSS, dumpToken, separator ) && std::getline( dumpSetSS, dumpSetToken, separator ) && dumpToken == dumpSetToken );//we read the common folders
    while( std::getline( dumpSetSS, dumpSetToken, separator ) ) //we read the nuber of tokens remaining in the dumpSet file.
    {                                                           //The last one doesn't count but since we skipped the first one (the last one read in the first loop) it evens up
        relativepPath += ".."; //that gives us the nuber of folders to go back
        relativepPath += separator;
    }
    relativepPath = relativepPath.append(dumpToken);    //then we add the end of the dump path
    while( std::getline( dumpSS, dumpToken, separator ) )
    {
        relativepPath = relativepPath.append(separator+dumpToken);
    }

    return relativepPath;
}
