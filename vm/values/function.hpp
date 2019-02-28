#ifndef VM_VALUES_FUNCTION_HPP_INCLUDED
#define VM_VALUES_FUNCTION_HPP_INCLUDED

#include "vm/values/value.hpp"

class IntCode;

class ScriptFunction : public ScriptValue
{
    private:
        IntCode* code;
    public:
        ScriptFunction(IntCode*);
        ~ScriptFunction();

        virtual void mark(GarbageCollector&);

        inline IntCode* getCode() const
        {
            return this->code;
        }
};

#endif // VM_VALUES_FUNCTION_HPP_INCLUDED
