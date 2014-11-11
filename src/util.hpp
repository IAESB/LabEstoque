#ifndef UTIL_HPP
#define UTIL_HPP


inline string to_string(const long double &_Val, const streamsize& precision)
{	// convert long double to string
    typedef back_insert_iterator<string> _Iter;
    typedef num_put<char, _Iter> _Nput;
    const _Nput& _Nput_fac = use_facet<_Nput>(locale());
    ostream _Ios((streambuf *)0);
    string _Str;

    _Ios.precision(precision);
    _Ios.setf(ios_base::fixed);
    _Nput_fac.put(_Iter(_Str), _Ios, ' ', _Val);
    return (_Str);
}

#endif // UTIL_HPP
