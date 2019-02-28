#include "vm/vm.hpp"
#include "vm/values/function.hpp"
#include "intcode/intcode.hpp"

VirtualMachine::VirtualMachine() {}

VirtualMachine::~VirtualMachine() {}

void VirtualMachine::execute_function(ScriptFunction* func)
{
    this->gc.addRoot(func);
    this->call_stack.push_back(func);

    IntCode* current_instr = func->getCode();

    while(current_instr != nullptr)
    {
        IntCode* next = current_instr->getNext();

        ///TODO: add actual instructions

        current_instr = next;
    }

    this->call_stack.pop_back();
    this->gc.removeRoot(func);
}

void VirtualMachine::execute(IntCode* bytecode)
{
    bytecode->addBlocks(this->gc);
    ScriptFunction* func = this->gc.makeValue<ScriptFunction>(bytecode);
    this->execute_function(func);
}
