#include "vm/scope.hpp"
#include "vm/gc.hpp"
#include "vm/values/table.hpp"

Scope::Scope(GarbageCollector& gc, Scope* enclosing) : enclosing(enclosing)
{
    this->table = gc.makeValue<ScriptTable>();
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

ScriptReference* Scope::lookup(const std::string& name, bool recurse)
{
    if(this->table->contains(name))
        return this->table->get(name);
    if(recurse)
    {
        if(this->enclosing != nullptr)
            return this->enclosing->lookup(name, true);
    }
    return nullptr;
}

ScriptReference* Scope::set(const std::string& name, ScriptValue* value, GarbageCollector& gc)
{
    this->table->set(name, value, gc);
    return this->table->get(name);
}
