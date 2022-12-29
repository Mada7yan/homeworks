#include "parallel_scheduler.h"
#include <iostream>
#include <unistd.h>
#include <pthread.h>

void* print(void* arg)
{
    int* num = (int*) arg;
    std::cout << "Printing " << *num << " from thread " << pthread_self() << std::endl;
    delete num;

    return NULL;
}

int main(int argc, const char** argv)
{
    thread_pool pool(10);
    pool.initialize();


    for(int i = 0; i < 1000; ++i)
    {
        int* number = new int(i);
        pool.run(pool_function_t(print, number));
    }

    sleep(100);

    return 0;
}

