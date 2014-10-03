#include "exception.h"

Exception::Exception(std::string m)
{
    msg = m;
}


const char *Exception::what()
{
    return msg.c_str();
}
