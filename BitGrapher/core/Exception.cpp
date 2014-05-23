#include "Exception.h"

Exception::Exception(std::string message) : m_message(message)
{
}

std::string Exception::getMessage()
{
    return m_message;
}
