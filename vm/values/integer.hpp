#ifndef VM_VALUES_INTEGER_HPP_INCLUDED
#define VM_VALUES_INTEGER_HPP_INCLUDED

#include "vm/values/value.hpp"

#include <cstdint>

class ScriptInteger : public ScriptValue
{
    private:
        int64_t value;
    public:
        ScriptInteger(int64_t);
        virtual ~ScriptInteger() = default;

        inline virtual ValueType getType() const
        {
            return ValueType::INTEGER;
        }

        inline virtual int64_t getInteger() const
        {
            return this->value;
        }
        inline virtual double getFloat() const
        {
            return this->value;
        }

        virtual std::string getString() const;
};

#endif // VM_VALUES_INTEGER_HPP_INCLUDED
