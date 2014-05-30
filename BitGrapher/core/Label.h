#ifndef LABEL_H
#define LABEL_H

#include <string>

struct Label
{
    std::string name;
    std::string encoding;
    std::string value;
    unsigned int index;
    unsigned int length;
};

#endif // LABEL_H
