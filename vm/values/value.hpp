#ifndef VM_VALUES_VALUE_HPP_INCLUDED
#define VM_VALUES_VALUE_HPP_INCLUDED

class GarbageCollector;

#include <cstdint>
#include <string>

enum class ValueType
{
    NULL_T,
    INTEGER,
    FLOAT,
    BOOLEAN,
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

        virtual double getFloat() const;
        virtual int64_t getInteger() const;
        virtual std::string getString() const = 0;
};

#endif // VM_VALUES_VALUE_HPP_INCLUDED
