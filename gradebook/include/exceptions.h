// File:   exceptions.h
// Author: Andre Wlodkovski
// Date:   20 Mar 2024
// Time:   18:30:00
// Brief:  This file contains all exceptions related to the GradeBook application.

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

/**
 * Class GradeBookException
 *
 * This class represents a generic GradeBook application error.
 */
class GradeBookException : public std::exception
{
public:
    GradeBookException(const std::string &message);
    virtual ~GradeBookException() = default;

    virtual char const *what() const noexcept;

protected:
    std::string message;
};

/**
 * Class GBResourceNotFoundException
 *
 * This class represents an error where a resource within GradeBook has not been found.
 */
class GBResourceNotFoundException : public GradeBookException
{
public:
    GBResourceNotFoundException(const std::string &message, const std::string &resourceId);
    virtual ~GBResourceNotFoundException() = default;
};

#endif