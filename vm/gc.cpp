#include "vm/gc.hpp"
#include "vm/values/value.hpp"
#include "intcode/intcode.hpp"
#include "vm/scope.hpp"
#include "vm/values/reference.hpp"

#include <algorithm>

GarbageCollector::GarbageCollector() {}

GarbageCollector::~GarbageCollector()
{
    //Cleanup what remains
    for(auto i : this->all_values)
        delete i;

    for(auto i : this->all_code)
        delete i;
}

bool GarbageCollector::mark(ScriptValue* value)
{
    if(std::find(this->unmarked_values.begin(), this->unmarked_values.end(), value) == this->unmarked_values.end())
        return false;
    this->unmarked_values.erase(std::remove(this->unmarked_values.begin(), this->unmarked_values.end(), value), this->unmarked_values.end());
    return true;
}

bool GarbageCollector::mark(IntCode* code)
{
    if(std::find(this->unmarked_code.begin(), this->unmarked_code.end(), code) == this->unmarked_code.end())
        return false;
    this->unmarked_code.erase(std::remove(this->unmarked_code.begin(), this->unmarked_code.end(), code), this->unmarked_code.end());
    return true;
}

bool GarbageCollector::mark(Scope* scope)
{
    if(std::find(this->unmarked_scopes.begin(), this->unmarked_scopes.end(), scope) == this->unmarked_scopes.end())
        return false;
    this->unmarked_scopes.erase(std::remove(this->unmarked_scopes.begin(), this->unmarked_scopes.end(), scope), this->unmarked_scopes.end());
    return true;
}

void GarbageCollector::addRoot(ScriptValue* value)
{
    this->root_values.push_back(value);
}

void GarbageCollector::addRoot(Scope* scope)
{
    this->root_scopes.push_back(scope);
}

void GarbageCollector::addValueStackRoot(std::vector<ScriptReference*>* root)
{
    this->root_value_stacks.push_back(root);
}

void GarbageCollector::removeRoot(ScriptValue* value)
{
    this->root_values.erase(std::remove(this->root_values.begin(), this->root_values.end(), value), this->root_values.end());
}

void GarbageCollector::removeRoot(Scope* scope)
{
    this->root_scopes.erase(std::remove(this->root_scopes.begin(), this->root_scopes.end(), scope), this->root_scopes.end());
}

void GarbageCollector::removeValueStackRoot(std::vector<ScriptReference*>* root)
{
    this->root_value_stacks.erase(std::remove(this->root_value_stacks.begin(), this->root_value_stacks.end(), root), this->root_value_stacks.end());
}

void GarbageCollector::cycle()
{
    this->collect(); ///TODO: Add a condition to the collection
}

void GarbageCollector::collect()
{
    //Add everything to the collector set
    this->unmarked_values.clear();
    for(auto i : this->all_values)
        this->unmarked_values.push_back(i);

    this->unmarked_code.clear();
    for(auto i : this->all_code)
        this->unmarked_code.push_back(i);

    this->unmarked_scopes.clear();
    for(auto i : this->all_scopes)
        this->unmarked_scopes.push_back(i);

    //Mark the roots
    for(auto i : this->root_values)
        i->mark(*this);

    for(auto i : this->root_scopes)
        i->mark(*this);

    for(auto& i : this->root_value_stacks)
    {
        for(auto j : *i)
            j->mark(*this);
    }

    //Collect what remains
    for(auto i : this->unmarked_values)
        delete i;

    for(auto i : this->unmarked_code)
        delete i;

    for(auto i : this->unmarked_scopes)
        delete i;
}

void GarbageCollector::addValue(ScriptValue* value)
{
    this->all_values.push_back(value);
}

void GarbageCollector::addCode(IntCode* code)
{
    this->all_code.push_back(code);
}

void GarbageCollector::addScope(Scope* scope)
{
    this->all_scopes.push_back(scope);
}
