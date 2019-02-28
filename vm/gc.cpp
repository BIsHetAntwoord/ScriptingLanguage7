#include "vm/gc.hpp"
#include "vm/values/value.hpp"
#include "intcode/intcode.hpp"

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

void GarbageCollector::mark(ScriptValue* value)
{
    this->unmarked_values.erase(std::remove(this->unmarked_values.begin(), this->unmarked_values.end(), value), this->unmarked_values.end());
}

void GarbageCollector::mark(IntCode* code)
{
    this->unmarked_code.erase(std::remove(this->unmarked_code.begin(), this->unmarked_code.end(), code), this->unmarked_code.end());
}

void GarbageCollector::addRoot(ScriptValue* value)
{
    this->root_values.push_back(value);
}

void GarbageCollector::removeRoot(ScriptValue* value)
{
    this->root_values.erase(std::remove(this->root_values.begin(), this->root_values.end(), value), this->root_values.end());
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

    //Mark the roots
    for(auto i : this->root_values)
        i->mark(*this);

    //Collect what remains
    for(auto i : this->unmarked_values)
        delete i;

    for(auto i : this->unmarked_code)
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
