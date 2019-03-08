#include "vm/values/bool.hpp"

ScriptBoolean::ScriptBoolean(bool value) : value(value) {}

std::string ScriptBoolean::getString() const
{
    return this->value ? "true" : "false";
}
