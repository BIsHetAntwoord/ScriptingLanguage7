#include "vm/values/reference.hpp"
#include "vm/gc.hpp"

#include <sstream>

ScriptReference::ScriptReference(ScriptValue* value) : value(value)
{

}

void ScriptReference::mark(GarbageCollector& gc)
{
    if(gc.mark(this))
        this->value->mark(gc);
}

std::string ScriptReference::getString() const
{
    std::stringstream ss;
    ss << "reference@" << this << "->" << this->value;
    return ss.str();
}
