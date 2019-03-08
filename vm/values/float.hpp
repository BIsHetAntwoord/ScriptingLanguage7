#ifndef VM_VALUES_FLOAT_HPP_INCLUDED
#define VM_VALUES_FLOAT_HPP_INCLUDED

#include "vm/values/value.hpp"

class ScriptFloat : public ScriptValue
{
    private:
        double value;
    public:
        ScriptFloat(double);
        virtual ~ScriptFloat() = default;

        inline virtual ValueType getType() const
        {
            return ValueType::FLOAT;
        }

        inline virtual double getFloat() const
        {
            return this->value;
        }
        inline virtual int64_t getInteger() const
        {
            return this->value;
        }

        virtual std::string getString() const;
};

#endif // VM_VALUES_FLOAT_HPP_INCLUDED
