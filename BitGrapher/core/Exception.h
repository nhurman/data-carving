#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>

class Exception
{
public:
    Exception(std::string message);
    std::string getMessage();

private:
    std::string m_message;
};

class BitStringException : Exception
{
    public: BitStringException(std::string message) : Exception(message) {}
};

class IOException : Exception
{
    public: IOException(std::string message) : Exception(message) {}
};

#endif // EXCEPTION_H
