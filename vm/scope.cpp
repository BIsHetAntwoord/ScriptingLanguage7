#include "vm/scope.hpp"
#include "vm/gc.hpp"
#include "vm/values/table.hpp"

Scope::Scope(GarbageCollector& gc, Scope* enclosing) : enclosing(enclosing)
{
    this->table = gc.makeValue<ScriptTable>();
}

Scope::~Scope()
{
}

void Scope::mark(GarbageCollector& gc)
{
    if(gc.mark(this))
    {
        this->table->mark(gc);
        if(this->enclosing != nullptr)
            this->enclosing->mark(gc);
    }
}
