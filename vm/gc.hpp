#ifndef VM_GC_HPP_INCLUDED
#define VM_GC_HPP_INCLUDED

#include <vector>

class ScriptValue;
class IntCode;

class GarbageCollector
{
    private:
        std::vector<ScriptValue*> all_values;
        std::vector<IntCode*> all_code;

        std::vector<ScriptValue*> unmarked_values;
        std::vector<IntCode*> unmarked_code;

        std::vector<ScriptValue*> root_values;
    public:
        GarbageCollector();
        ~GarbageCollector();

        void mark(ScriptValue*);
        void mark(IntCode*);

        void addRoot(ScriptValue*);
        void removeRoot(ScriptValue*);

        void cycle();
        void collect();

        void addValue(ScriptValue*);
        void addCode(IntCode*);

        template <typename T, typename... Args>
        T* makeValue(Args&&... args)
        {
            T* result = new T(args...);
            this->addValue(result);
            return result;
        }
};

#endif // VM_GC_HPP_INCLUDED
