#include "vm/values/value.hpp"
#include "vm/gc.hpp"

ScriptValue::ScriptValue()
{
}

ScriptValue::~ScriptValue() {}

void ScriptValue::mark(GarbageCollector& gc)
{
    gc.mark(this);
}
