#ifndef VM_VALUES_VALUE_HPP_INCLUDED
#define VM_VALUES_VALUE_HPP_INCLUDED

class GarbageCollector;

enum class ValueType
{
    NULL_T,
    INTEGER,
    FLOAT,
    STRING,
    TABLE,
    REFERENCE,
    FUNCTION
};

class ScriptValue
{
    protected:
        ScriptValue();
    public:
        virtual ~ScriptValue() = 0;

        virtual void mark(GarbageCollector&);
        virtual ValueType getType() const = 0;
};

#endif // VM_VALUES_VALUE_HPP_INCLUDED
