#include "vm/values/reference.hpp"
#include "vm/gc.hpp"

ScriptReference::ScriptReference(ScriptValue* value) : value(value)
{

}

void ScriptReference::mark(GarbageCollector& gc)
{
    if(gc.mark(this))
        this->value->mark(gc);
}
