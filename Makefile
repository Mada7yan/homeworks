all: thread_pool_app

thread_pool_app: main.o thread.o
	g++ main.o thread.o -pthread -o thread_pool_app

main.o: main.cpp parallel_scheduler.h pool_function_t.h
	g++ -c main.cpp -o main.o

thread.o: parallel_scheduler.cpp
	g++ -c parallel_scheduler.cpp -pthread -o thread.o	


clean:
	rm *.o thread_pool_app
