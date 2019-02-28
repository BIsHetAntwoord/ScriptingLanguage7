#include "vm/values/function.hpp"
#include "vm/gc.hpp"
#include "intcode/intcode.hpp"

ScriptFunction::ScriptFunction(IntCode* code) : code(code) {}

ScriptFunction::~ScriptFunction() {}

void ScriptFunction::mark(GarbageCollector& gc)
{
    ScriptValue::mark(gc);

    this->code->mark(gc);
}
