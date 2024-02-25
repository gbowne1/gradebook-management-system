#include "../include/exceptions.h"
#include <iostream>

GradeBookException::GradeBookException(const std::string &message)
    : std::exception(), message(message)
{
    std::cerr << "GradeBookException: " << message << std::endl;
}

char const *GradeBookException::what() const noexcept
{
    return this->message.c_str();
}

GBResourceNotFoundException::GBResourceNotFoundException(const std::string &message, const std::string &resourceId)
    : GradeBookException("Resource not found: " + message + " (ID: " + resourceId + ")")
{
    // Example logging with resource ID
    std::cerr << "GBResourceNotFoundException: Resource not found. ID: " << resourceId << std::endl;
}