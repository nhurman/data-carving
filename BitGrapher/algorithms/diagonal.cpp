#include "algorithms/diagonal.h"

Diagonal::Diagonal(unsigned int posX, unsigned int posY, size_t length) : m_x(posX), m_y(posY), m_length(length) {}

Diagonal::~Diagonal() {}

unsigned int Diagonal::getX() const {
    return m_x;
}

unsigned int Diagonal::getY() const {
    return m_y;
}

size_t Diagonal::length() const {
    return m_length;
}

std::string Diagonal::toString() const{
    std::stringstream ss;
    ss <<"x = " << m_x << "; y = " << m_y << "; length = " << m_length;
    return ss.str();
}

int Diagonal::minStringSize(std::list<int> sizes)
{
    int t = 0; //nb of combinations of 2 bits from different dumps
    for(std::list<int>::iterator i = sizes.begin(); i != sizes.end(); i++)
    {
        std::list<int>::iterator j = i;
        for(j++; j != sizes.end(); j++) //j starts at i+1
        {
            t+= (*i)*(*j);
        }
    }
    return 4.29 + std::log2(t) + .99; //+.99 : cheap way to round up the result
}
