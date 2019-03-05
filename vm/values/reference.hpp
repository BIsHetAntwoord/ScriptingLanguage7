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
};

#endif // VM_VALUES_REFERENCE_HPP_INCLUDED
