#ifndef VM_VALUES_REFERENCE_HPP_INCLUDED
#define VM_VALUES_REFERENCE_HPP_INCLUDED

#include "vm/values/value.hpp"

class ScriptReference : public ScriptValue
{
    private:
        ScriptValue* value;
    public:
        ScriptReference(ScriptValue*);
        virtual ~ScriptReference() = default;

        virtual void mark(GarbageCollector&);

        inline ScriptValue* getValue() const
        {
            return this->value;
        }
        inline void setValue(ScriptValue* value)
        {
            this->value = value;
        }

        inline virtual ValueType getType() const
        {
            return ValueType::REFERENCE;
        }
};

#endif // VM_VALUES_REFERENCE_HPP_INCLUDED
