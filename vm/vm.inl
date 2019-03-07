#include "vm/values/value.hpp"
#include "vm/values/reference.hpp"
#include "vm/values/float.hpp"
#include "vm/values/integer.hpp"

ScriptValue* resolve_reference(ScriptValue*);
bool can_arithmetic(ScriptValue*);

const ValueType BINOP_TYPE_TABLE[7][7] = {
    //NULL                  //INTEGER           //FLOAT             //STRING            //TABLE             //REFERENCE         //FUNCTION
    {ValueType::INTEGER,    ValueType::INTEGER, ValueType::FLOAT,   ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T}, //NULL
    {ValueType::INTEGER,    ValueType::INTEGER, ValueType::FLOAT,   ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T}, //INTEGER
    {ValueType::FLOAT,      ValueType::FLOAT,   ValueType::FLOAT,   ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T}, //FLOAT
    {ValueType::NULL_T,     ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T}, //STRING
    {ValueType::NULL_T,     ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T}, //TABLE
    {ValueType::NULL_T,     ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T}, //REFERENCE
    {ValueType::NULL_T,     ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T,  ValueType::NULL_T}  //FUNCTION
};

template <typename T>
void VirtualMachine::execute_binop(T callback)
{
    ScriptReference* rop = this->value_stack->back();
    this->value_stack->pop_back();
    ScriptReference* lop = this->value_stack->back();
    this->value_stack->pop_back();

    ScriptValue* lop_value = resolve_reference(lop);
    ScriptValue* rop_value = resolve_reference(rop);

    ValueType operation_type = BINOP_TYPE_TABLE[size_t(lop_value->getType())][size_t(rop_value->getType())];

    if(operation_type == ValueType::FLOAT)
    {
        auto result = callback(lop_value->getFloat(), rop_value->getFloat());
        this->value_stack->push_back(this->gc.makeValue<ScriptReference>(this->gc.makeValue<ScriptFloat>(result)));
    }
    else if(operation_type == ValueType::INTEGER)
    {
        auto result = callback(lop_value->getInteger(), rop_value->getInteger());
        this->value_stack->push_back(this->gc.makeValue<ScriptReference>(this->gc.makeValue<ScriptInteger>(result)));
    }
    else
    {
        this->throw_exception("Attempted to perform arithmetic on non-arithmetic types");
    }
}
