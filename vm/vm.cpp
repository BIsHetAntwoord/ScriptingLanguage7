#include "vm/vm.hpp"
#include "vm/values/function.hpp"
#include "vm/values/null.hpp"
#include "vm/values/integer.hpp"
#include "vm/values/reference.hpp"
#include "vm/values/string.hpp"
#include "vm/values/table.hpp"
#include "intcode/intcode.hpp"
#include "intcode/intinstr.hpp"
#include "vm/scope.hpp"

#include <cmath>
#include <iostream>

using instr_callback = void(VirtualMachine::*)(IntCode*, IntCode*&);

const instr_callback INSTR_CALLBACKS[] = {
    VirtualMachine::execute_nop,
    VirtualMachine::execute_store,
    VirtualMachine::execute_pop,
    VirtualMachine::execute_load,
    VirtualMachine::execute_add,
    VirtualMachine::execute_sub,
    VirtualMachine::execute_mul,
    VirtualMachine::execute_div,
    VirtualMachine::execute_mod,
    VirtualMachine::execute_bitand,
    VirtualMachine::execute_bitor,
    VirtualMachine::execute_bitxor,
    VirtualMachine::execute_uplus,
    VirtualMachine::execute_neg,
    VirtualMachine::execute_compl,
    VirtualMachine::execute_pushint,
    VirtualMachine::execute_pushflt,
    VirtualMachine::execute_try,
    VirtualMachine::execute_try_end
};

ScriptValue* resolve_reference(ScriptValue* ref)
{
    while(ref->getType() == ValueType::REFERENCE)
        ref = ((ScriptReference*)ref)->getValue();

    return ref;
}

int64_t mod(int64_t x, int64_t y)
{
    return x % y;
}

double mod(double x, double y)
{
    return std::fmod(x, y);
}

VirtualMachine::VirtualMachine()
{
    this->global_scope = this->gc.makeScope(this->gc);
    this->gc.addRoot(this->global_scope);
}

VirtualMachine::~VirtualMachine() {}

void VirtualMachine::execute_function(ScriptFunction* func)
{
    this->gc.addRoot(func);
    this->call_stack.push_back(func);
    this->exception_stack.emplace_back();

    std::vector<ScriptReference*> local_value_stack;
    std::vector<ScriptReference*>* enclosing_value_stack = this->value_stack;
    this->value_stack = &local_value_stack;

    Scope* current_scope = this->gc.makeScope(this->gc, func->getEnclosingScope());
    this->gc.addRoot(current_scope);
    this->scope_stack.push_back(current_scope);

    this->gc.addValueStackRoot(this->value_stack);

    IntCode* current_instr = func->getCode();

    while(current_instr != nullptr)
    {
        IntCode* next = current_instr->getNext();

        IntInstr op = current_instr->getOp();

        (this->*INSTR_CALLBACKS[size_t(op)])(current_instr, next);

        if(this->exception_state)
        {
            if(!this->handle_exception(next))
            {
                ScriptReference* ref = this->value_stack->back();
                this->value_stack->pop_back();
                //Unhandled exception, push it to the calling function
                if(enclosing_value_stack != nullptr)
                    enclosing_value_stack->push_back(ref);
                else
                {
                    ///TODO: actually parse the exception info
                    this->termination_msg = resolve_reference(ref)->getString();
                }
                break;
            }
        }

        this->gc.cycle();

        current_instr = next;
    }

    current_scope->getTable()->foreach([](ScriptValue* key, ScriptReference* value) {
        std::cout << "Variable " << key->getString() << " -> " << resolve_reference(value)->getString() << std::endl;
    });

    this->gc.removeValueStackRoot(this->value_stack);

    this->value_stack = enclosing_value_stack;

    this->gc.removeRoot(current_scope);
    this->scope_stack.pop_back();

    this->call_stack.pop_back();
    this->exception_stack.pop_back();
    this->gc.removeRoot(func);
}

bool VirtualMachine::execute(IntCode* bytecode, std::string* msg)
{
    bytecode->addBlocks(this->gc);
    ScriptFunction* func = this->gc.makeValue<ScriptFunction>(bytecode, this->global_scope);
    this->execute_function(func);

    if(this->exception_state)
    {
        if(msg != nullptr)
            *msg = this->termination_msg;
    }
    return !this->exception_state;
}

void VirtualMachine::throw_exception()
{
    this->exception_state = true;
}

void VirtualMachine::throw_exception(const std::string& arg)
{
    this->value_stack->push_back(this->gc.makeValue<ScriptReference>(this->gc.makeValue<ScriptString>(arg)));
    this->throw_exception();
}

bool VirtualMachine::handle_exception(IntCode*& next)
{
    size_t stack_unwind;
    bool has_handler = this->exception_stack.back().getHandler(next, stack_unwind);

    if(has_handler)
    {
        ScriptReference* top_of_stack = this->value_stack->back();

        while(this->value_stack->size() > stack_unwind)
            this->value_stack->pop_back();

        this->value_stack->push_back(top_of_stack);
    }
    return has_handler;
}

void VirtualMachine::execute_nop(IntCode*, IntCode*&) {}

void VirtualMachine::execute_store(IntCode*, IntCode*&)
{
    ScriptReference* value = this->value_stack->back();
    this->value_stack->pop_back();
    ScriptReference* ref = this->value_stack->back();

    //Go to the lowest reference
    while(ref->getValue()->getType() == ValueType::REFERENCE)
        ref = (ScriptReference*)ref->getValue();

    ref->setValue(resolve_reference(value));
}

void VirtualMachine::execute_pop(IntCode*, IntCode*&)
{
    this->value_stack->pop_back();
}

void VirtualMachine::execute_load(IntCode* instr, IntCode*&)
{
    Scope* current_scope = this->scope_stack.back();

    StrIntInstr* instr_str = (StrIntInstr*)instr;
    ScriptReference* ref = current_scope->lookup(instr_str->getStr(), true);
    if(ref == nullptr)
    {
        //Create the variable
        ScriptValue* value = this->gc.makeValue<ScriptNull>();
        ref = current_scope->set(instr_str->getStr(), value, this->gc);
    }
    this->value_stack->push_back(ref);
}

void VirtualMachine::execute_add(IntCode*, IntCode*&)
{
    this->execute_binop([](auto x, auto y) {return x + y;});
}

void VirtualMachine::execute_sub(IntCode*, IntCode*&)
{
    this->execute_binop([](auto x, auto y) {return x - y;});
}

void VirtualMachine::execute_mul(IntCode*, IntCode*&)
{
    this->execute_binop([](auto x, auto y) {return x * y;});
}

void VirtualMachine::execute_div(IntCode*, IntCode*&)
{
    this->execute_binop([this](auto x, auto y) {
        if(std::is_integral<decltype(y)>::value)
        {
            if(y == (decltype(y))0)
            {
                this->throw_exception("Integer division by zero");
                return (decltype(y))0;
            }
        }
        return x / y;
    });
}

void VirtualMachine::execute_mod(IntCode*, IntCode*&)
{
    this->execute_binop([this](auto x, auto y) {
        if(std::is_integral<decltype(y)>::value)
        {
            if(y == (decltype(y))0)
            {
                this->throw_exception("Integer division by zero");
                return (decltype(y))0;
            }
        }
        return mod(x, y);
    });
}

void VirtualMachine::execute_bitand(IntCode*, IntCode*&)
{
    this->execute_int_binop([](int64_t x, int64_t y) {return x & y;});
}

void VirtualMachine::execute_bitor(IntCode*, IntCode*&)
{
    this->execute_int_binop([](int64_t x, int64_t y) {return x | y;});
}

void VirtualMachine::execute_bitxor(IntCode*, IntCode*&)
{
    this->execute_int_binop([](int64_t x, int64_t y) {return x ^ y;});
}

void VirtualMachine::execute_uplus(IntCode*, IntCode*&)
{
    ScriptReference* ref = this->value_stack->back();
    this->value_stack->pop_back();

    ScriptValue* val = resolve_reference(ref);
    if(val->getType() == ValueType::FLOAT)
    {
        this->value_stack->push_back(this->gc.makeValue<ScriptReference>(this->gc.makeValue<ScriptFloat>(val->getFloat())));
    }
    else if(val->getType() == ValueType::INTEGER)
    {
        this->value_stack->push_back(this->gc.makeValue<ScriptReference>(this->gc.makeValue<ScriptInteger>(val->getInteger())));
    }
    else
    {
        this->throw_exception("Attempted to perform arithmetic on a non-arithmetic type");
    }
}

void VirtualMachine::execute_neg(IntCode*, IntCode*&)
{
    ScriptReference* ref = this->value_stack->back();
    this->value_stack->pop_back();

    ScriptValue* val = resolve_reference(ref);
    if(val->getType() == ValueType::FLOAT)
    {
        this->value_stack->push_back(this->gc.makeValue<ScriptReference>(this->gc.makeValue<ScriptFloat>(-val->getFloat())));
    }
    else if(val->getType() == ValueType::INTEGER)
    {
        this->value_stack->push_back(this->gc.makeValue<ScriptReference>(this->gc.makeValue<ScriptInteger>(-val->getInteger())));
    }
    else
    {
        this->throw_exception("Attempted to perform arithmetic on a non-arithmetic type");
    }
}

void VirtualMachine::execute_compl(IntCode*, IntCode*&)
{
    ScriptReference* ref = this->value_stack->back();
    this->value_stack->pop_back();

    ScriptValue* val = resolve_reference(ref);
    if(val->getType() == ValueType::INTEGER)
    {
        this->value_stack->push_back(this->gc.makeValue<ScriptReference>(this->gc.makeValue<ScriptInteger>(~val->getInteger())));
    }
    else
    {
        this->throw_exception("Attempted to perform integer arithmetic on a non-integer type");
    }
}

void VirtualMachine::execute_pushint(IntCode* instr, IntCode*&)
{
    IntegerIntInstr* int_instr = (IntegerIntInstr*)instr;
    int64_t value = int_instr->getInteger();
    this->value_stack->push_back(gc.makeValue<ScriptReference>(gc.makeValue<ScriptInteger>(value)));
}

void VirtualMachine::execute_pushflt(IntCode* instr, IntCode*&)
{
    FloatIntInstr* flt_instr = (FloatIntInstr*)instr;
    double value = flt_instr->getFloat();
    this->value_stack->push_back(gc.makeValue<ScriptReference>(gc.makeValue<ScriptFloat>(value)));
}

void VirtualMachine::execute_try(IntCode* current, IntCode*&)
{
    TargetIntInstr* current_target = (TargetIntInstr*)current;
    IntCode* target = current_target->getTarget();

    ExceptionInfo& info = this->exception_stack.back();
    info.addHandler(target, this->value_stack->size());
}

void VirtualMachine::execute_try_end(IntCode*, IntCode*&)
{
    ExceptionInfo& info = this->exception_stack.back();
    info.removeHandler();
}
