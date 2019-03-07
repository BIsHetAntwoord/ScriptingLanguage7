#include "vm/vm.hpp"
#include "vm/values/function.hpp"
#include "vm/values/null.hpp"
#include "intcode/intcode.hpp"
#include "intcode/intinstr.hpp"
#include "vm/scope.hpp"

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
    VirtualMachine::execute_try,
    VirtualMachine::execute_try_end
};

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
                break;
        }

        current_instr = next;
    }

    this->gc.removeValueStackRoot(this->value_stack);

    this->value_stack = enclosing_value_stack;

    this->gc.removeRoot(current_scope);
    this->scope_stack.pop_back();

    this->call_stack.pop_back();
    this->exception_stack.pop_back();
    this->gc.removeRoot(func);
}

void VirtualMachine::execute(IntCode* bytecode)
{
    bytecode->addBlocks(this->gc);
    ScriptFunction* func = this->gc.makeValue<ScriptFunction>(bytecode, this->global_scope);
    this->execute_function(func);
}

void VirtualMachine::throw_exception()
{
    this->exception_state = true;
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

void VirtualMachine::execute_store(IntCode*, IntCode*&) {}

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

void VirtualMachine::execute_add(IntCode*, IntCode*&) {}
void VirtualMachine::execute_sub(IntCode*, IntCode*&) {}
void VirtualMachine::execute_mul(IntCode*, IntCode*&) {}
void VirtualMachine::execute_div(IntCode*, IntCode*&) {}
void VirtualMachine::execute_mod(IntCode*, IntCode*&) {}
void VirtualMachine::execute_bitand(IntCode*, IntCode*&) {}
void VirtualMachine::execute_bitor(IntCode*, IntCode*&) {}
void VirtualMachine::execute_bitxor(IntCode*, IntCode*&) {}
void VirtualMachine::execute_uplus(IntCode*, IntCode*&) {}
void VirtualMachine::execute_neg(IntCode*, IntCode*&) {}
void VirtualMachine::execute_compl(IntCode*, IntCode*&) {}
void VirtualMachine::execute_pushint(IntCode*, IntCode*&) {}

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
