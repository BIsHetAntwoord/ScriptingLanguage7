#include "vm/gc.hpp"
#include "vm/values/value.hpp"
#include "intcode/intcode.hpp"
#include "vm/scope.hpp"
#include "vm/values/reference.hpp"

#include <algorithm>
#include <iostream>

GarbageCollector::GarbageCollector() {}

GarbageCollector::~GarbageCollector()
{
    //Cleanup what remains
    for(auto i : this->all_values)
    {
        //std::cout << "Deleting value at destruction: "  << this << " (" << i->getString() << ")" << std::endl;
        delete i;
    }

    for(auto i : this->all_code)
    {
        //std::cout << "Deleting code at destruction: " << this << std::endl;
        delete i;
    }

    for(auto i : this->all_scopes)
    {
        //std::cout << "Deleting scope at destruction: " << this << std::endl;
        delete i;
    }
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
    ///TODO: add a decent collection scheme
    if(++this->cycle_counter == 20)
    {
        this->cycle_counter = 0;
        this->collect();
    }
}

void GarbageCollector::collect()
{
    //std::cout << "Starting collect phase" << std::endl;
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
    {
        //std::cout << "Collecting value at " << i << " (" << i->getString() << ")" << std::endl;
        this->removeValue(i);
        delete i;
    }

    for(auto i : this->unmarked_code)
    {
        //std::cout << "Collecting code at " << i << std::endl;
        this->removeCode(i);
        delete i;
    }

    for(auto i : this->unmarked_scopes)
    {
        //std::cout << "Collecting scope at " << i << std::endl;
        this->removeScope(i);
        delete i;
    }

    //std::cout << "End of collect phase" << std::endl;
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

void GarbageCollector::removeValue(ScriptValue* value)
{
    this->all_values.erase(std::remove(this->all_values.begin(), this->all_values.end(), value), this->all_values.end());
}

void GarbageCollector::removeCode(IntCode* code)
{
    this->all_code.erase(std::remove(this->all_code.begin(), this->all_code.end(), code), this->all_code.end());
}

void GarbageCollector::removeScope(Scope* scope)
{
    this->all_scopes.erase(std::remove(this->all_scopes.begin(), this->all_scopes.end(), scope), this->all_scopes.end());
}
