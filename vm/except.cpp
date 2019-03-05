#include "vm/except.hpp"

void ExceptionInfo::addHandler(IntCode* resume, size_t unwind)
{
    this->resume_handlers.push_back(resume);
    this->stack_unwind.push_back(unwind);
}

void ExceptionInfo::removeHandler()
{
    this->resume_handlers.pop_back();
    this->stack_unwind.pop_back();
}

bool ExceptionInfo::getHandler(IntCode*& resume, size_t& unwind)
{
    if(this->resume_handlers.size() > 0)
    {
        resume = this->resume_handlers.back();
        unwind = this->stack_unwind.back();
        return true;
    }
    return false;
}
