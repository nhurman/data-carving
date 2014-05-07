#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include <string>
#include "bitstring.h"
#include "encoding/Encoding.h"
#include <vector>

struct Field {
    std::string fieldName;
    unsigned int start;
    unsigned int end;
    //Encoding decoder;
};

class Association
{
public:
    Association();
    Association(BitString const* bs);
    void setData(BitString const* bs);
    void addField();
    void addField(std::string name, const unsigned int start, const unsigned int end);
    void editField(unsigned int pos, std::string name, const unsigned int start, const unsigned int end);
    void move(unsigned int moveFrom, unsigned int moveTo);
    void remove(unsigned int pos);


private:
    BitString const* m_data;
    std::vector<struct Field> m_fieldsList;
};

#endif // ASSOCIATION_H
