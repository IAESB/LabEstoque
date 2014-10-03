#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <boost/exception/all.hpp>

class Exception : public boost::exception, std::exception
{
    std::string msg;
public:
    Exception(std::string msg);
    virtual const char* what();
};

#endif // EXCEPTION_H
