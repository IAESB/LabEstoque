#ifndef UTIL_HPP
#define UTIL_HPP

#include <iomanip>

inline string to_string(const long double &_Val, const streamsize& precision)
{	// convert long double to string

    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << _Val;
    return out.str();
}

#endif // UTIL_HPP
