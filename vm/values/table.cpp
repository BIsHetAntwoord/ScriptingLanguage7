#include "vm/values/table.hpp"
#include "vm/gc.hpp"
#include "vm/values/reference.hpp"

ScriptTable::ScriptTable() {}

void ScriptTable::mark(GarbageCollector& gc)
{
    if(gc.mark(this))
    {
        for(auto& it : this->values)
        {
            it.first->mark(gc);
            it.second->mark(gc);
        }
    }
}
