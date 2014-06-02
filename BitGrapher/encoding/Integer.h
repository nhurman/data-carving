#ifndef INTEGER_H
#define INTEGER_H

#include "encoding/Encoding2.h"

/*!
 * \class Integer
 * \brief Raw integer encoding
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
class Integer : public Encoding2
{
public:
    Integer();
    std::string getChunk(unsigned int index) const;
};

/*!
 * \class Integer
 * \brief Raw unsigned integer encoding over 2 bits
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
class Integer2 : public Integer
{
public:
    Integer2() : Integer() {}
    unsigned int bitsPerChunk() const { return 2; }
    std::string getName() const { return "Int2"; }
};

/*!
 * \class Integer
 * \brief Raw unsigned integer encoding over 3 bits
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
class Integer3 : public Integer
{
public:
    Integer3() : Integer() {}
    unsigned int bitsPerChunk() const { return 3; }
    std::string getName() const { return "Int3"; }
};

/*!
 * \class Integer
 * \brief Raw unsigned integer encoding over 4 bits
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
class Integer4 : public Integer
{
public:
    Integer4() : Integer() {}
    unsigned int bitsPerChunk() const { return 4; }
    std::string getName() const { return "Int4"; }
};

/*!
 * \class Integer
 * \brief Raw unsigned integer encoding over 5 bits
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
class Integer5 : public Integer
{
public:
    Integer5() : Integer() {}
    unsigned int bitsPerChunk() const { return 5; }
    std::string getName() const { return "Int5"; }
};

/*!
 * \class Integer
 * \brief Raw unsigned integer encoding over 6 bits
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
class Integer6 : public Integer
{
public:
    Integer6() : Integer() {}
    unsigned int bitsPerChunk() const { return 6; }
    std::string getName() const { return "Int6"; }
};

/*!
 * \class Integer
 * \brief Raw unsigned integer encoding over 7 bits
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
class Integer7 : public Integer
{
public:
    Integer7() : Integer() {}
    unsigned int bitsPerChunk() const { return 7; }
    std::string getName() const { return "Int7"; }
};

/*!
 * \class Integer
 * \brief Raw unsigned integer encoding over 8 bits
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
class Integer8 : public Integer
{
public:
    Integer8() : Integer() {}
    unsigned int bitsPerChunk() const { return 8; }
    std::string getName() const { return "Int8"; }
};

/*!
 * \class Integer
 * \brief Raw unsigned integer encoding over 16 bits
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
class Integer16 : public Integer
{
public:
    Integer16() : Integer() {}
    unsigned int bitsPerChunk() const { return 16; }
    std::string getName() const { return "Int16"; }
};

/*!
 * \class Integer
 * \brief Raw unsigned integer encoding over 32 bits
 *
 * \author Nicolas Hurman
 * \date 28/05/2014
 */
class Integer32 : public Integer
{
public:
    Integer32() : Integer() {}
    unsigned int bitsPerChunk() const { return 32; }
    std::string getName() const { return "Int32"; }
};

#endif // INTEGER_H
