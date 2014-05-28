#include "Diagonal.h"


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


