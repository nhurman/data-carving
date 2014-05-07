#include "Association.h"

Association::Association()
{
}

Association::Association(BitString const* bs) : m_data(bs)
{
}

void Association::setData(BitString const* bs)
{
     m_data = bs;
}

void Association::addField()
{
    m_fieldsList.push_back(Field());
}

void Association::addField(std::string name, const unsigned int start, const unsigned int end)
{
    m_fieldsList.push_back({name, start, end});
}

void Association::editField(unsigned int pos, std::string name, const unsigned int start, const unsigned int end) {
    m_fieldsList[pos] = {name, start, end};
}

// seem easier to interact with the interface with numbers rather than iterators
void Association::move(unsigned int moveFrom, unsigned int moveTo) {
    m_fieldsList.insert(m_fieldsList.begin() + moveTo, m_fieldsList[moveFrom]);
    m_fieldsList.erase(m_fieldsList.begin() + moveFrom + 1);
}

void Association::remove(unsigned int pos) {
    m_fieldsList.erase(m_fieldsList.begin() + pos);

}
