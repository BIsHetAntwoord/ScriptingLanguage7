#ifndef VM_VALUES_FUNCTION_HPP_INCLUDED
#define VM_VALUES_FUNCTION_HPP_INCLUDED

#include "vm/values/value.hpp"

class IntCode;
class Scope;

class ScriptFunction : public ScriptValue
{
    private:
        IntCode* code;
        Scope* enclosing;
    public:
        ScriptFunction(IntCode*, Scope*);
        ~ScriptFunction();

        virtual void mark(GarbageCollector&);

        inline IntCode* getCode() const
        {
            return this->code;
        }

        inline Scope* getEnclosingScope() const
        {
            return this->enclosing;
        }

        inline virtual ValueType getType() const
        {
            return ValueType::FUNCTION;
        }
};

#endif // VM_VALUES_FUNCTION_HPP_INCLUDED
