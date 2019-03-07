#ifndef VM_VM_HPP_INCLUDED
#define VM_VM_HPP_INCLUDED

#include <vector>
#include <string>

#include "vm/gc.hpp"
#include "vm/except.hpp"

class IntCode;
class ScriptFunction;
class ScriptReference;

class VirtualMachine
{
    private:
        GarbageCollector gc;
        Scope* global_scope;
        std::vector<ScriptFunction*> call_stack;
        std::vector<ExceptionInfo> exception_stack;
        std::vector<ScriptReference*>* value_stack;
        std::vector<Scope*> scope_stack;
        bool exception_state = false;

        void execute_function(ScriptFunction*);

        void throw_exception();
        void throw_exception(const std::string&);
        bool handle_exception(IntCode*&);

        template <typename T>
        void execute_binop(T callback);
    public:
        VirtualMachine();
        ~VirtualMachine();

        void execute(IntCode*);

        //Instructions
        void execute_nop(IntCode*, IntCode*&);
        void execute_store(IntCode*, IntCode*&);
        void execute_pop(IntCode*, IntCode*&);
        void execute_load(IntCode*, IntCode*&);

        void execute_add(IntCode*, IntCode*&);
        void execute_sub(IntCode*, IntCode*&);
        void execute_mul(IntCode*, IntCode*&);
        void execute_div(IntCode*, IntCode*&);
        void execute_mod(IntCode*, IntCode*&);
        void execute_bitand(IntCode*, IntCode*&);
        void execute_bitor(IntCode*, IntCode*&);
        void execute_bitxor(IntCode*, IntCode*&);

        void execute_uplus(IntCode*, IntCode*&);
        void execute_neg(IntCode*, IntCode*&);
        void execute_compl(IntCode*, IntCode*&);

        void execute_pushint(IntCode*, IntCode*&);

        void execute_try(IntCode*, IntCode*&);
        void execute_try_end(IntCode*, IntCode*&);
};

#include "vm/vm.inl"

#endif // VM_HPP_INCLUDED
