#ifndef INTINSTR_HPP_INCLUDED
#define INTINSTR_HPP_INCLUDED

#include "intcode/intcode.hpp"

#include <string>

class BaseIntInstr : public IntCode
{
    public:
        BaseIntInstr(IntInstr);
        virtual ~BaseIntInstr() = default;

        virtual void print(std::ostream&);
};

class StrIntInstr : public IntCode
{
    private:
        std::string str;
    public:
        StrIntInstr(IntInstr, const std::string&);
        virtual ~StrIntInstr() = default;

        virtual void print(std::ostream&);
};

class IntegerIntInstr : public IntCode
{
    private:
        uint64_t integer;
    public:
        IntegerIntInstr(IntInstr, uint64_t);
        virtual ~IntegerIntInstr() = default;

        virtual void print(std::ostream&);
};

class TargetIntInstr : public IntCode
{
    private:
        IntCode* target;
    public:
        TargetIntInstr(IntInstr, IntCode*);
        virtual ~TargetIntInstr() = default;

        virtual void print(std::ostream&);

        inline IntCode* getTarget() const
        {
            return this->target;
        }
};

#endif // INTINSTR_HPP_INCLUDED
