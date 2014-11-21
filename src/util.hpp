#ifndef UTIL_HPP
#define UTIL_HPP

#include <iomanip>
#include <sstream>

inline std::string to_string(const long double &_Val, const streamsize& precision)
{	// convert long double to string

    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << _Val;
    return out.str();
}

inline std::string to_string(const std::tm& tm, const char* format = "%F")
{
    std::tm _default = std::tm();
    if(difftime(mktime((std::tm*)&tm), mktime(&_default)) == 0)
        return "";

    char buffer [80];
    strftime (buffer,80, format, &tm);
    return buffer;
}

#if _MSC_VER || __MINGW32__
#	define makedir(x) mkdir(x)
#else
#	define makedir(x) mkdir(x, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif

#endif // UTIL_HPP
