#ifndef SCRIPT_VALUES_NULL_HPP_INCLUDED
#define SCRIPT_VALUES_NULL_HPP_INCLUDED

#include "vm/values/value.hpp"

class ScriptNull : public ScriptValue
{
    public:
        ScriptNull() = default;
        virtual ~ScriptNull() = default;

        inline virtual ValueType getType() const
        {
            return ValueType::NULL_T;
        }

        inline virtual int64_t getInteger() const
        {
            return 0;
        }
        inline virtual double getFloat() const
        {
            return 0.0;
        }

        inline virtual std::string getString() const
        {
            return "null";
        }
};

#endif // SCRIPT_VALUES_NULL_HPP_INCLUDED
