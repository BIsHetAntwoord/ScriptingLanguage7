#include "vm/values/float.hpp"

ScriptFloat::ScriptFloat(double val) : value(val) {}

std::string ScriptFloat::getString() const
{
    return std::to_string(this->value);
}
