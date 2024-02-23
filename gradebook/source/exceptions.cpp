#include "exceptions.h"

GradeBookException::GradeBookException(const std::string &message)
    : std::exception(), message(message)
{
}

char const *GradeBookException::what() const noexcept
{
    return this->message.c_str();
}

GBResourceNotFoundException::GBResourceNotFoundException(const std::string &message)
    : GradeBookException(message)
{
}