#ifndef VM_GC_HPP_INCLUDED
#define VM_GC_HPP_INCLUDED

#include <vector>

class ScriptValue;
class IntCode;
class Scope;
class ScriptReference;

class GarbageCollector
{
    private:
        std::vector<ScriptValue*> all_values;
        std::vector<IntCode*> all_code;
        std::vector<Scope*> all_scopes;

        std::vector<ScriptValue*> unmarked_values;
        std::vector<IntCode*> unmarked_code;
        std::vector<Scope*> unmarked_scopes;

        std::vector<ScriptValue*> root_values;
        std::vector<Scope*> root_scopes;
        std::vector<std::vector<ScriptReference*>*> root_value_stacks;

        size_t cycle_counter = 0;
    public:
        GarbageCollector();
        ~GarbageCollector();

        bool mark(ScriptValue*);
        bool mark(IntCode*);
        bool mark(Scope*);

        void addRoot(ScriptValue*);
        void removeRoot(ScriptValue*);
        void addRoot(Scope*);
        void removeRoot(Scope*);
        void addValueStackRoot(std::vector<ScriptReference*>*);
        void removeValueStackRoot(std::vector<ScriptReference*>*);

        void cycle();
        void collect();

        void addValue(ScriptValue*);
        void addCode(IntCode*);
        void addScope(Scope*);

        void removeValue(ScriptValue*);
        void removeCode(IntCode*);
        void removeScope(Scope*);

        template <typename T, typename... Args>
        T* makeValue(Args&&... args)
        {
            T* result = new T(args...);
            this->addValue(result);
            return result;
        }

        template <typename... Args>
        Scope* makeScope(Args&&... args)
        {
            Scope* result = new Scope(args...);
            this->addScope(result);
            return result;
        }
};

#endif // VM_GC_HPP_INCLUDED
