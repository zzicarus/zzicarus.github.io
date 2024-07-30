#include <pthread.h>
#include <iostream>
using namespace std;

void *thread_func(void *arg)
{
    // 线程要执行的代码
}

int main()
{
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    cout << "PID" << thread << endl;
    pthread_join(thread, NULL);
    return 0;
}
