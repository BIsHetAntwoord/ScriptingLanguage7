#ifndef VM_SCOPE_HPP_INCLUDED
#define VM_SCOPE_HPP_INCLUDED

#include <vector>
#include <string>

class GarbageCollector;
class ScriptTable;
class ScriptReference;
class ScriptValue;

class Scope
{
    private:
        Scope* enclosing;
        ScriptTable* table;
    public:
        Scope(GarbageCollector&, Scope* = nullptr);
        ~Scope() = default;

        inline ScriptTable* getTable()
        {
            return this->table;
        }

        inline Scope* getEnclosing()
        {
            return this->enclosing;
        }

        void mark(GarbageCollector&);

        ScriptReference* lookup(const std::string&, bool);
        ScriptReference* set(const std::string&, ScriptValue*, GarbageCollector&);
};

#endif // VM_SCOPE_HPP_INCLUDED
