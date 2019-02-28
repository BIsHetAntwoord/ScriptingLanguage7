#ifndef STRINGS_HPP_INCLUDED
#define STRINGS_HPP_INCLUDED

#include <string>
#include <sstream>

template <typename... T>
std::string make_str(const T&... values)
{
    std::stringstream ss;
    ((ss << values), ...);
    return ss.str();
}

#endif // STRINGS_HPP_INCLUDED
