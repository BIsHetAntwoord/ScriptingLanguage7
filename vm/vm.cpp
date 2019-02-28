#include "vm/vm.hpp"

VirtualMachine::VirtualMachine(IntCode* bytecode)
{

}

VirtualMachine::~VirtualMachine()
{

}

void VirtualMachine::execute_function(ScriptFunction* func)
{
    this->call_stack.push_back(func);


}

void VirtualMachine::execute()
{
    ScriptFunction* base_func = this->call_stack[0];
    this->call_stack.pop_back();
    this->execute_function(base_func);
}
