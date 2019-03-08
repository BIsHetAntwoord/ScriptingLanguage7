#ifndef VM_VALUES_STRING_HPP_INCLUDED
#define VM_VALUES_STRING_HPP_INCLUDED

#include "vm/values/value.hpp"

#include <string>

class ScriptString : public ScriptValue
{
    private:
        std::string value;
    public:
        ScriptString(const std::string&);
        virtual ~ScriptString() = default;

        inline virtual ValueType getType() const
        {
            return ValueType::STRING;
        }

        inline virtual std::string getString() const
        {
            return this->value;
        }
};

#endif // VM_VALUES_STRING_HPP_INCLUDED
