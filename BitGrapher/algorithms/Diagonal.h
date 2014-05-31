#ifndef DIAGONAL_H
#define DIAGONAL_H

//#include <cmath>
#include <string>
#include <sstream>
#include <list>

/// \class Diagonal
///
/// \brief Objects created by dot plot algorithm.
///
/// \author Gaugry Thierry
///
/// \date 24/05/2014

class Diagonal
{
public:


    /// \brief A constructor for Diagonal.
    /// \param posX X position of the upper left point.
    /// \param posY Y position of the upper left point.
    /// \param length Length of the diagonal.
    /// \note Only fill the fields of the object.
    Diagonal(unsigned int posX, unsigned int posY, size_t length);

    /// \brief A destructor for Diagonal.
    ~Diagonal();

    /// \brief Return the value of m_x.
    /// \return X position of the upper left point.
    unsigned int getX() const;

    /// \brief Return the value of m_y.
    /// \return X position of the upper left point.
    unsigned int getY() const;

    /// \brief Return the value of m_lentgh.
    /// \return Length of the diagonal.
    size_t length() const;

    /// \brief Allow to see the object in a more user-friendly way.
    /// \return String with all atributes.
    /// \note  Output look like x = m_x ; y =  m_y  ; length =  m_length.
    std::string toString() const;

    //probabilities
    static int minStringSize(std::list<int> sizes); //give it the dump sizes

private:
    unsigned int m_x; ///<  X position of the upper left point.
    unsigned int m_y; ///<  Y position of the upper left point.
    size_t m_length; ///<  Length of the diagonal.

};

#endif // DIAGONAL_H
