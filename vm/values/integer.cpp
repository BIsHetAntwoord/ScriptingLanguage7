#include "vm/values/integer.hpp"

ScriptInteger::ScriptInteger(int64_t value) : value(value) {}

std::string ScriptInteger::getString() const
{
    return std::to_string(this->value);
}
