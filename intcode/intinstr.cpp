#include "intcode/intinstr.hpp"

#include <iostream>

const char* OPCODE_NAMES[] = {
    "NOP",

    "STORE",
    "POP",
    "LOAD",

    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "MOD",
    "BITAND",
    "BITOR",
    "BITXOR",

    "UPLUS",
    "NEG",
    "COMPL",

    "PUSHINT"
};

BaseIntInstr::BaseIntInstr(IntInstr op) : IntCode(op) {}

void BaseIntInstr::print(std::ostream& os)
{
    os << OPCODE_NAMES[size_t(this->op)] << std::endl;
    if(this->next)
        this->next->print(os);
}

StrIntInstr::StrIntInstr(IntInstr op, const std::string& str) : IntCode(op), str(str) {}

void StrIntInstr::print(std::ostream& os)
{
    os << OPCODE_NAMES[size_t(this->op)] << " " << this->str << std::endl;
    if(this->next)
        this->next->print(os);
}

IntegerIntInstr::IntegerIntInstr(IntInstr op, uint64_t value) : IntCode(op), integer(value) {}

void IntegerIntInstr::print(std::ostream& os)
{
    os << OPCODE_NAMES[size_t(this->op)] << " " << this->integer << std::endl;
    if(this->next)
        this->next->print(os);
}
