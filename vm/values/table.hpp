#ifndef VM_VALUES_TABLE_HPP_INCLUDED
#define VM_VALUES_TABLE_HPP_INCLUDED

#include "vm/values/value.hpp"

#include <unordered_map>

class ScriptReference;

class ScriptTable : public ScriptValue
{
    private:
        std::unordered_map<ScriptValue*, ScriptReference*> values;
    public:
        ScriptTable();
        virtual ~ScriptTable() = default;

        virtual void mark(GarbageCollector& gc);
};

#endif // VM_VALUES_TABLE_HPP_INCLUDED
