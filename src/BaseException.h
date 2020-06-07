#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H
#include <iostream>
#include <string>

/*
    Virtual base class for Exception
*/
namespace PlanetDefenders
{
    class BaseException
    {
    protected:
        std::string msg;
    public:
        BaseException(const std::string& message) : msg(message) {}
        virtual const std::string message() = 0;
    };
}

#endif
