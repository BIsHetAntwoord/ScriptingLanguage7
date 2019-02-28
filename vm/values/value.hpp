#ifndef VM_VALUES_VALUE_HPP_INCLUDED
#define VM_VALUES_VALUE_HPP_INCLUDED

class GarbageCollector;

class ScriptValue
{
    protected:
        ScriptValue();
    public:
        virtual ~ScriptValue() = 0;

        virtual void mark(GarbageCollector&);
};

#endif // VM_VALUES_VALUE_HPP_INCLUDED
