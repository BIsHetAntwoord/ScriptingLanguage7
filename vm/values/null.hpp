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
};

#endif // SCRIPT_VALUES_NULL_HPP_INCLUDED
