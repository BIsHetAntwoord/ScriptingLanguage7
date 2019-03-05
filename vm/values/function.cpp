#include "vm/values/function.hpp"
#include "vm/gc.hpp"
#include "intcode/intcode.hpp"
#include "vm/scope.hpp"

ScriptFunction::ScriptFunction(IntCode* code, Scope* enclosing) : code(code), enclosing(enclosing) {}

ScriptFunction::~ScriptFunction() {}

void ScriptFunction::mark(GarbageCollector& gc)
{
    if(gc.mark(this))
    {
        this->code->mark(gc);
        this->enclosing->mark(gc);
    }
}
