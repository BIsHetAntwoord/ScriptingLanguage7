#ifndef INTCODE_HPP_INCLUDED
#define INTCODE_HPP_INCLUDED

#include <iosfwd>

class TreeNode;
class GarbageCollector;

enum class IntInstr
{
    NOP,

    STORE,
    POP,
    LOAD,

    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    BITAND,
    BITOR,
    BITXOR,

    UPLUS,
    NEG,
    COMPL,

    PUSHINT
};

struct compile_info
{

};

class IntCode
{
    protected:
        IntInstr op;
        IntCode* next = nullptr;

        IntCode(IntInstr);
    public:
        virtual ~IntCode();

        static IntCode* generate(TreeNode*, const compile_info&);

        void setNext(IntCode*);
        IntCode* getNext() const;

        virtual void print(std::ostream&) = 0;
        virtual void mark(GarbageCollector&, bool = true);
        virtual void addBlocks(GarbageCollector&, bool = true);
};

#endif // INTCODE_HPP_INCLUDED
