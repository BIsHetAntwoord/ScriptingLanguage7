#include "vm/values/value.hpp"
#include "vm/gc.hpp"

#include <limits>

ScriptValue::ScriptValue()
{
}

ScriptValue::~ScriptValue() {}

void ScriptValue::mark(GarbageCollector& gc)
{
    gc.mark(this);
}

double ScriptValue::getFloat() const
{
    return std::numeric_limits<double>::quiet_NaN();
}

int64_t ScriptValue::getInteger() const
{
    return 0;
}
