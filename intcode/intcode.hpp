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
    CONCAT,

    UPLUS,
    NEG,
    COMPL,

    PUSHINT,
    PUSHFLT,
    PUSHSTR,
    PUSHBOOL,

    TRY,
    TRY_END
};

struct compile_info
{

};

class IntCode
{
    protected:
        IntInstr op;
        IntCode* next = nullptr;
        size_t ip;

        IntCode(IntInstr);
    public:
        virtual ~IntCode();

        static IntCode* generate(TreeNode*, const compile_info&);

        void setNext(IntCode*);
        IntCode* getNext() const;

        inline IntInstr getOp() const
        {
            return this->op;
        }

        virtual void print(std::ostream&) = 0;
        virtual void mark(GarbageCollector&, bool = true);
        virtual void addBlocks(GarbageCollector&, bool = true);

        void setIP(size_t);

        inline size_t getIP() const
        {
            return this->ip;
        }
};

#endif // INTCODE_HPP_INCLUDED
