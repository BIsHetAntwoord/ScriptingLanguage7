#ifndef TREENODE_HPP_INCLUDED
#define TREENODE_HPP_INCLUDED

#include <memory>

#include <iosfwd>

struct compile_info;
class IntCode;

class TreeNode
{
    public:
        virtual ~TreeNode() = default;

        virtual void print(std::ostream&, size_t = 0) = 0;

        virtual IntCode* generate(const compile_info&) = 0;
};

class StatementNode : public TreeNode
{
    public:
        virtual ~StatementNode() = 0;
};

class StatementListNode : public StatementNode
{
    private:
        std::unique_ptr<StatementNode> left;
        std::unique_ptr<StatementNode> right;
    public:
        StatementListNode(StatementNode*, StatementNode*);
        virtual ~StatementListNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class EmptyNode : public StatementNode
{
    public:
        EmptyNode() = default;
        virtual ~EmptyNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class ExpressionNode;

class ExpressionStatementNode : public StatementNode
{
    private:
        std::unique_ptr<ExpressionNode> op;
    public:
        ExpressionStatementNode(ExpressionNode*);
        virtual ~ExpressionStatementNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class ExpressionNode : public TreeNode
{
    public:
        ExpressionNode() = default;
        virtual ~ExpressionNode() = 0;
};

class AssignNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> lop;
        std::unique_ptr<ExpressionNode> rop;
    public:
        AssignNode(ExpressionNode*, ExpressionNode*);
        virtual ~AssignNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class AddNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> lop;
        std::unique_ptr<ExpressionNode> rop;
    public:
        AddNode(ExpressionNode*, ExpressionNode*);
        virtual ~AddNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class SubNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> lop;
        std::unique_ptr<ExpressionNode> rop;
    public:
        SubNode(ExpressionNode*, ExpressionNode*);
        virtual ~SubNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class MulNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> lop;
        std::unique_ptr<ExpressionNode> rop;
    public:
        MulNode(ExpressionNode*, ExpressionNode*);
        virtual ~MulNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class DivNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> lop;
        std::unique_ptr<ExpressionNode> rop;
    public:
        DivNode(ExpressionNode*, ExpressionNode*);
        virtual ~DivNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class ModNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> lop;
        std::unique_ptr<ExpressionNode> rop;
    public:
        ModNode(ExpressionNode*, ExpressionNode*);
        virtual ~ModNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class BitAndNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> lop;
        std::unique_ptr<ExpressionNode> rop;
    public:
        BitAndNode(ExpressionNode*, ExpressionNode*);
        virtual ~BitAndNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class BitOrNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> lop;
        std::unique_ptr<ExpressionNode> rop;
    public:
        BitOrNode(ExpressionNode*, ExpressionNode*);
        virtual ~BitOrNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class BitXorNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> lop;
        std::unique_ptr<ExpressionNode> rop;
    public:
        BitXorNode(ExpressionNode*, ExpressionNode*);
        virtual ~BitXorNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class ConcatNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> lop;
        std::unique_ptr<ExpressionNode> rop;
    public:
        ConcatNode(ExpressionNode*, ExpressionNode*);
        virtual ~ConcatNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class UPlusNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> op;
    public:
        UPlusNode(ExpressionNode*);
        virtual ~UPlusNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class UMinNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> op;
    public:
        UMinNode(ExpressionNode*);
        virtual ~UMinNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class BitNotNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> op;
    public:
        BitNotNode(ExpressionNode*);
        virtual ~BitNotNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class TryNode : public ExpressionNode
{
    private:
        std::unique_ptr<ExpressionNode> op;
    public:
        TryNode(ExpressionNode*);
        virtual ~TryNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class VariableNode : public ExpressionNode
{
    private:
        std::string name;
    public:
        VariableNode(const std::string&);
        virtual ~VariableNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class ConstantNode : public ExpressionNode
{
    public:
        ConstantNode() = default;
        virtual ~ConstantNode() = 0;
};

class IntegerNode : public ConstantNode
{
    private:
        uint64_t value;
    public:
        IntegerNode(uint64_t);
        virtual ~IntegerNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class FloatNode : public ConstantNode
{
    private:
        double value;
    public:
        FloatNode(double);
        virtual ~FloatNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class StringNode : public ConstantNode
{
    private:
        std::string value;
    public:
        StringNode(const std::string&);
        virtual ~StringNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

class BoolNode : public ConstantNode
{
    private:
        bool value;
    public:
        BoolNode(bool);
        virtual ~BoolNode() = default;

        virtual void print(std::ostream&, size_t);
        virtual IntCode* generate(const compile_info&);
};

#endif // TREENODE_HPP_INCLUDED
