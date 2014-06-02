#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

/*!
 * \class Exception
 * \brief Exceptions thrown by the core
 *
 * \author Nicolas Hurman
 * \date 01/03/2014
 */
class Exception
{
public:
    /*!
     * \brief Constructor with the exception message
     * \param message Exception details
     */
    Exception(std::string message);

    /*!
     * \brief Returns this exception's message
     * \return Exception details
     */
    std::string getMessage();

private:
    std::string m_message;
};

/*!
 * \class BitStringException
 * \brief BitString errors
 *
 * \author Nicolas Hurman
 * \date 01/03/2014
 */
class BitStringException : Exception
{
    /*!
     * \brief Constructor with the exception message
     * \param message Exception details
     */
    public: BitStringException(std::string message) : Exception(message) {}
};

/*!
 * \class IOException
 * \brief File handling errors
 *
 * \author Nicolas Hurman
 * \date 01/03/2014
 */
class IOException : Exception
{
    /*!
     * \brief Constructor with the exception message
     * \param message Exception details
     */
    public: IOException(std::string message) : Exception(message) {}
};

#endif // EXCEPTION_H
