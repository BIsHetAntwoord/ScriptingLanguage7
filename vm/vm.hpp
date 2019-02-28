#ifndef VM_VM_HPP_INCLUDED
#define VM_VM_HPP_INCLUDED

#include <vector>

#include "vm/gc.hpp"

class IntCode;
class ScriptFunction;

class VirtualMachine
{
    private:
        GarbageCollector gc;
        std::vector<ScriptFunction*> call_stack;

        void execute_function(ScriptFunction*);
    public:
        VirtualMachine();
        ~VirtualMachine();

        void execute(IntCode*);
};

#endif // VM_HPP_INCLUDED
