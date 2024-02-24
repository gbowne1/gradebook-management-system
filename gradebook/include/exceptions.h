#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>


class GradeBookException : public std::exception
{
public:
    GradeBookException(const std::string &message);
    virtual ~GradeBookException() = default;

    virtual char const *what() const noexcept;

protected:
    std::string message;
};

class GBResourceNotFoundException : public GradeBookException
{
public:
    GBResourceNotFoundException(const std::string &message, const std::string &resourceId);
    virtual ~GBResourceNotFoundException() = default;
};

#endif