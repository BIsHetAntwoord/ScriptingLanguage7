#ifndef VM_SCOPE_HPP_INCLUDED
#define VM_SCOPE_HPP_INCLUDED

#include <vector>

class GarbageCollector;
class ScriptTable;

class Scope
{
    private:
        Scope* enclosing;
        ScriptTable* table;
    public:
        Scope(GarbageCollector&, Scope* = nullptr);
        ~Scope();

        inline ScriptTable* getTable()
        {
            return this->table;
        }

        inline Scope* getEnclosing()
        {
            return this->enclosing;
        }

        void mark(GarbageCollector&);
};

#endif // VM_SCOPE_HPP_INCLUDED
