#ifndef POOL_FUNCTION_T_H
#define POOL_FUNCTION_T_H

typedef void* (*thread_function_t) (void*);

class pool_function_t
{
private:
    thread_function_t function;
    void* argument;
public:
    pool_function_t(thread_function_t func, void* arg): function(func), argument(arg) {}

    inline thread_function_t get_function()
    {
        return this->function;
    }

    inline void* get_argument()
    {
        return this->argument;
    }
};

#endif
