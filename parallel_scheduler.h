#ifndef PARALLEL_SCHEDULER_H
#define PARALLEL_SCHEDULER_H

#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include "pool_function_t.h"


class thread_pool
{
private:
    std::queue<pool_function_t>* queue;
    std::size_t size;
    pthread_mutex_t* queue_lock;
    sem_t* empty;
    pthread_t* threads;

    static void* thread_function(void* arg);
public:
    thread_pool(std::size_t size);
    void initialize();
    void run(pool_function_t pool_function);
    ~thread_pool();
};




#endif
