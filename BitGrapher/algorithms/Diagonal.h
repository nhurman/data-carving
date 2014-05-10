#ifndef DIAGONAL_H
#define DIAGONAL_H

//#include <cmath>
#include <string>
#include <sstream>
//#include <list>

//#define LOG2(x) std::log(x)/log(2)

class Diagonal
{
public:
    Diagonal(unsigned int posX, unsigned int posY, size_t length);
    ~Diagonal();
    unsigned int getX() const;
    unsigned int getY() const;
    size_t length() const;
    std::string toString() const;

    //probabilities
    //static int minStringSize(std::list<int> sizes); //give it the dump sizes

private:
    unsigned int m_x;
    unsigned int m_y;
    size_t m_length;

};

#endif // DIAGONAL_H
