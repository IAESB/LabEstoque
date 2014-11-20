#ifndef UTIL_HPP
#define UTIL_HPP

#include <iomanip>

inline string to_string(const long double &_Val, const streamsize& precision)
{	// convert long double to string

    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << _Val;
    return out.str();
}

#if _MSC_VER || __MINGW32__
#	define makedir(x) mkdir(x)
#else
#	define makedir(x) mkdir(x, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif

#endif // UTIL_HPP
