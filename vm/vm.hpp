#ifndef VM_VM_HPP_INCLUDED
#define VM_VM_HPP_INCLUDED

#include <vector>

class IntCode;

class VirtualMachine
{
    private:
        std::vector<ScriptFunction*> call_stack;

        void execute_function(ScriptFunction*);
    public:
        VirtualMachine(IntCode*);
        ~VirtualMachine();

        void execute();
};

#endif // VM_HPP_INCLUDED
