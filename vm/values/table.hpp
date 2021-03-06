#ifndef VM_VALUES_TABLE_HPP_INCLUDED
#define VM_VALUES_TABLE_HPP_INCLUDED

#include "vm/values/value.hpp"

#include <unordered_map>
#include <string>

class ScriptReference;

class ScriptTable : public ScriptValue
{
    private:
        std::unordered_map<ScriptValue*, ScriptReference*> values;
    public:
        ScriptTable();
        virtual ~ScriptTable() = default;

        virtual void mark(GarbageCollector& gc);

        inline virtual ValueType getType() const
        {
            return ValueType::TABLE;
        }

        virtual std::string getString() const;

        bool contains(const std::string&);
        ScriptReference* get(const std::string&);
        void set(const std::string&, ScriptValue*, GarbageCollector&);

        template <typename T>
        void foreach(T callback);
};

#include "vm/values/table.inl"

#endif // VM_VALUES_TABLE_HPP_INCLUDED
