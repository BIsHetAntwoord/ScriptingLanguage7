#include "vm/values/table.hpp"
#include "vm/gc.hpp"
#include "vm/values/reference.hpp"
#include "vm/values/string.hpp"

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

bool ScriptTable::contains(const std::string& name)
{
    return this->get(name) != nullptr;
}

ScriptReference* ScriptTable::get(const std::string& name)
{
    for(auto& it : this->values)
    {
        if(it.first->getType() == ValueType::STRING)
        {
            ScriptString* str = (ScriptString*)it.first;
            if(str->getStr() == name)
                return it.second;
        }
    }
    return nullptr;
}

void ScriptTable::set(const std::string& name, ScriptValue* value, GarbageCollector& gc)
{
    ScriptReference* val = this->get(name);
    if(val == nullptr)
        this->values[gc.makeValue<ScriptString>(name)] = gc.makeValue<ScriptReference>(value);
    else
        val->setValue(value);
}
