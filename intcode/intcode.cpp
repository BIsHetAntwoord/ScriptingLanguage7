#include "intcode/intcode.hpp"
#include "intcode/intinstr.hpp"
#include "intcode/treenode.hpp"
#include "vm/gc.hpp"

#include <memory>

IntCode* concat(IntCode* left, IntCode* right)
{
    IntCode* left_orig = left;
    IntCode* next = left->getNext();
    while(next != nullptr)
    {
        left = next;
        next = left->getNext();
    }

    left->setNext(right);
    return left_orig;
}

IntCode::IntCode(IntInstr op) : op(op) {}

IntCode::~IntCode()
{
    delete this->next;
}

void IntCode::mark(GarbageCollector& gc, bool mark_self)
{
    if(mark_self)
        gc.mark(this);

    if(this->next)
        this->next->mark(gc, false);
}

void IntCode::addBlocks(GarbageCollector& gc, bool mark_self)
{
    if(mark_self)
        gc.addCode(this);

    if(this->next)
        this->next->addBlocks(gc, false);
}

void IntCode::setNext(IntCode* next)
{
    this->next = next;
}

IntCode* IntCode::getNext() const
{
    return this->next;
}

IntCode* StatementListNode::generate(const compile_info& info)
{
    std::unique_ptr<IntCode> lop(this->left->generate(info));
    std::unique_ptr<IntCode> rop(this->right->generate(info));

    return concat(lop.release(), rop.release());
}

IntCode* EmptyNode::generate(const compile_info&)
{
    return new BaseIntInstr(IntInstr::NOP);
}

IntCode* ExpressionStatementNode::generate(const compile_info& info)
{
    std::unique_ptr<IntCode> op(this->op->generate(info));
    std::unique_ptr<IntCode> pop(new BaseIntInstr(IntInstr::POP));

    return concat(op.release(), pop.release());
}

IntCode* AssignNode::generate(const compile_info& info)
{
    std::unique_ptr<IntCode> lop(this->lop->generate(info));
    std::unique_ptr<IntCode> rop(this->rop->generate(info));
    std::unique_ptr<IntCode> store(new BaseIntInstr(IntInstr::STORE));

    return concat(concat(lop.release(), rop.release()), store.release());
}

IntCode* AddNode::generate(const compile_info& info)
{
    std::unique_ptr<IntCode> lop(this->lop->generate(info));
    std::unique_ptr<IntCode> rop(this->rop->generate(info));
    std::unique_ptr<IntCode> operation(new BaseIntInstr(IntInstr::ADD));

    return concat(concat(lop.release(), rop.release()), operation.release());
}

IntCode* SubNode::generate(const compile_info& info)
{
    std::unique_ptr<IntCode> lop(this->lop->generate(info));
    std::unique_ptr<IntCode> rop(this->rop->generate(info));
    std::unique_ptr<IntCode> operation(new BaseIntInstr(IntInstr::SUB));

    return concat(concat(lop.release(), rop.release()), operation.release());
}

IntCode* MulNode::generate(const compile_info& info)
{
    std::unique_ptr<IntCode> lop(this->lop->generate(info));
    std::unique_ptr<IntCode> rop(this->rop->generate(info));
    std::unique_ptr<IntCode> operation(new BaseIntInstr(IntInstr::MUL));

    return concat(concat(lop.release(), rop.release()), operation.release());
}

IntCode* DivNode::generate(const compile_info& info)
{
    std::unique_ptr<IntCode> lop(this->lop->generate(info));
    std::unique_ptr<IntCode> rop(this->rop->generate(info));
    std::unique_ptr<IntCode> operation(new BaseIntInstr(IntInstr::DIV));

    return concat(concat(lop.release(), rop.release()), operation.release());
}

IntCode* ModNode::generate(const compile_info& info)
{
    std::unique_ptr<IntCode> lop(this->lop->generate(info));
    std::unique_ptr<IntCode> rop(this->rop->generate(info));
    std::unique_ptr<IntCode> operation(new BaseIntInstr(IntInstr::MOD));

    return concat(concat(lop.release(), rop.release()), operation.release());
}

IntCode* BitAndNode::generate(const compile_info& info)
{
    std::unique_ptr<IntCode> lop(this->lop->generate(info));
    std::unique_ptr<IntCode> rop(this->rop->generate(info));
    std::unique_ptr<IntCode> operation(new BaseIntInstr(IntInstr::BITAND));

    return concat(concat(lop.release(), rop.release()), operation.release());
}

IntCode* BitOrNode::generate(const compile_info& info)
{
    std::unique_ptr<IntCode> lop(this->lop->generate(info));
    std::unique_ptr<IntCode> rop(this->rop->generate(info));
    std::unique_ptr<IntCode> operation(new BaseIntInstr(IntInstr::BITOR));

    return concat(concat(lop.release(), rop.release()), operation.release());
}

IntCode* BitXorNode::generate(const compile_info& info)
{
    std::unique_ptr<IntCode> lop(this->lop->generate(info));
    std::unique_ptr<IntCode> rop(this->rop->generate(info));
    std::unique_ptr<IntCode> operation(new BaseIntInstr(IntInstr::BITXOR));

    return concat(concat(lop.release(), rop.release()), operation.release());
}

IntCode* UPlusNode::generate(const compile_info& info)
{
    std::unique_ptr<IntCode> op(this->op->generate(info));
    std::unique_ptr<IntCode> operation(new BaseIntInstr(IntInstr::UPLUS));

    return concat(op.release(), operation.release());
}

IntCode* UMinNode::generate(const compile_info& info)
{
    std::unique_ptr<IntCode> op(this->op->generate(info));
    std::unique_ptr<IntCode> operation(new BaseIntInstr(IntInstr::NEG));

    return concat(op.release(), operation.release());
}

IntCode* BitNotNode::generate(const compile_info& info)
{
    std::unique_ptr<IntCode> op(this->op->generate(info));
    std::unique_ptr<IntCode> operation(new BaseIntInstr(IntInstr::COMPL));

    return concat(op.release(), operation.release());
}

IntCode* VariableNode::generate(const compile_info& info)
{
    return new StrIntInstr(IntInstr::LOAD, this->name);
}

IntCode* IntegerNode::generate(const compile_info& info)
{
    return new IntegerIntInstr(IntInstr::PUSHINT, this->value);
}
