#include "intcode/treenode.hpp"

#include <iostream>

void print_indent(std::ostream& os, size_t level)
{
    for(size_t i = 0; i < level; ++i)
        os << "    ";
}

StatementNode::~StatementNode() {}

StatementListNode::StatementListNode(StatementNode* lop, StatementNode* rop) : left(lop), right(rop) {}

void StatementListNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Statement List:" << std::endl;
    this->left->print(os, level+1);
    this->right->print(os, level+1);
}

void EmptyNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Empty Node" << std::endl;
}

ExpressionStatementNode::ExpressionStatementNode(ExpressionNode* op) : op(op) {}

void ExpressionStatementNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Expression Statement:" << std::endl;
    this->op->print(os, level+1);
}

ExpressionNode::~ExpressionNode() {}

AssignNode::AssignNode(ExpressionNode* lop, ExpressionNode* rop) : lop(lop), rop(rop) {}

void AssignNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Assignment Expression:" << std::endl;
    this->lop->print(os, level+1);
    this->rop->print(os, level+1);
}

AddNode::AddNode(ExpressionNode* lop, ExpressionNode* rop) : lop(lop), rop(rop) {}

void AddNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Add Expression:" << std::endl;
    this->lop->print(os, level+1);
    this->rop->print(os, level+1);
}

SubNode::SubNode(ExpressionNode* lop, ExpressionNode* rop) : lop(lop), rop(rop) {}

void SubNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Sub Expression:" << std::endl;
    this->lop->print(os, level+1);
    this->rop->print(os, level+1);
}

MulNode::MulNode(ExpressionNode* lop, ExpressionNode* rop) : lop(lop), rop(rop) {}

void MulNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Multiplication Expression:" << std::endl;
    this->lop->print(os, level+1);
    this->rop->print(os, level+1);
}

DivNode::DivNode(ExpressionNode* lop, ExpressionNode* rop) : lop(lop), rop(rop) {}

void DivNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Division Expression:" << std::endl;
    this->lop->print(os, level+1);
    this->rop->print(os, level+1);
}

ModNode::ModNode(ExpressionNode* lop, ExpressionNode* rop) : lop(lop), rop(rop) {}

void ModNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Modulo Expression:" << std::endl;
    this->lop->print(os, level+1);
    this->rop->print(os, level+1);
}

BitAndNode::BitAndNode(ExpressionNode* lop, ExpressionNode* rop) : lop(lop), rop(rop) {}

void BitAndNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Bitwise And Expression:" << std::endl;
    this->lop->print(os, level+1);
    this->rop->print(os, level+1);
}

BitOrNode::BitOrNode(ExpressionNode* lop, ExpressionNode* rop) : lop(lop), rop(rop) {}

void BitOrNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Bitwise Or Expression:" << std::endl;
    this->lop->print(os, level+1);
    this->rop->print(os, level+1);
}

BitXorNode::BitXorNode(ExpressionNode* lop, ExpressionNode* rop) : lop(lop), rop(rop) {}

void BitXorNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Bitwise Xor Expression:" << std::endl;
    this->lop->print(os, level+1);
    this->rop->print(os, level+1);
}

UPlusNode::UPlusNode(ExpressionNode* op) : op(op) {}

void UPlusNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Unary Plus Expression:" << std::endl;
    this->op->print(os, level+1);
}

UMinNode::UMinNode(ExpressionNode* op) : op(op) {}

void UMinNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Unary Min Expression:" << std::endl;
    this->op->print(os, level+1);
}

BitNotNode::BitNotNode(ExpressionNode* op) : op(op) {}

void BitNotNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Bitwise Not Expression:" << std::endl;
    this->op->print(os, level+1);
}

TryNode::TryNode(ExpressionNode* op) : op(op) {}

void TryNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Try Expression:" << std::endl;
    this->op->print(os, level+1);
}

VariableNode::VariableNode(const std::string& name) : name(name) {}

void VariableNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Variable (" << this->name << ")" << std::endl;
}

ConstantNode::~ConstantNode() {}

IntegerNode::IntegerNode(uint64_t value) : value(value) {}

void IntegerNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Integer (" << this->value << ")" << std::endl;
}

FloatNode::FloatNode(double value) : value(value) {}

void FloatNode::print(std::ostream& os, size_t level)
{
    print_indent(os, level);
    os << "Float (" << this->value << ")" << std::endl;
}
