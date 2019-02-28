#ifndef EXCEPTIONS_HPP_INCLUDED
#define EXCEPTIONS_HPP_INCLUDED

#include "util/strings.hpp"

#include <stdexcept>

class CompilerException : public std::runtime_error
{
    public:
        template <typename... T>
        CompilerException(const T&... values) : std::runtime_error(make_str(values...)) {}

        ~CompilerException() = default;
};

class ParseException : public CompilerException
{
    public:
        template <typename... T>
        ParseException(const T&... values) : CompilerException(values...) {}

        ~ParseException() = default;
};

#endif // EXCEPTIONS_HPP_INCLUDED
