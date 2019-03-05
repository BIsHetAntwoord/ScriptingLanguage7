#ifndef EXCEPT_HPP_INCLUDED
#define EXCEPT_HPP_INCLUDED

#include <cstddef>
#include <vector>

class IntCode;

class ExceptionInfo
{
    private:
        std::vector<IntCode*> resume_handlers;
        std::vector<size_t> stack_unwind;
    public:
        ExceptionInfo() = default;
        ~ExceptionInfo() = default;

        void addHandler(IntCode*, size_t);
        void removeHandler();

        bool getHandler(IntCode*&, size_t&);
};

#endif // EXCEPT_HPP_INCLUDED
