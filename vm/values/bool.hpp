#ifndef VM_VALUES_BOOL_HPP_INCLUDED
#define VM_VALUES_BOOL_HPP_INCLUDED

#include "vm/values/value.hpp"

class ScriptBoolean : public ScriptValue
{
    private:
        bool value;
    public:
        ScriptBoolean(bool);
        virtual ~ScriptBoolean() = default;

        inline virtual ValueType getType() const
        {
            return ValueType::BOOLEAN;
        }

        inline virtual int64_t getInteger() const
        {
            return this->value ? 1 : 0;
        }

        inline virtual double getFloat() const
        {
            return this->value ? 1.0 : 0.0;
        }

        virtual std::string getString() const;
};

#endif // VM_VALUES_BOOL_HPP_INCLUDED
