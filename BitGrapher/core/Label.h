#ifndef LABEL_H
#define LABEL_H

#include <string>

/*!
 * \class Label
 * \brief Represents a label
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
struct Label
{
    std::string name;
    std::string encoding;
    std::string value;
    unsigned int index;
    unsigned int length;
};

#endif // LABEL_H
