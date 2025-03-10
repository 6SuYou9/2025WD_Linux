#include <2025Linux.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
int main(int argc,char *argv[])
{
    pthread_mutexattr_t mutexattr;  // 锁属性类型
    pthread_mutex_t mutex;          // 锁的类型
    pthread_mutexattr_init(&mutexattr);     // 初始化锁属性
    pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_ERRORCHECK);     // 把锁属性设置为检错锁
    pthread_mutex_init(&mutex,&mutexattr);  // 动态初始化锁，设置为检错锁

    int ret = pthread_mutex_lock(&mutex);
    THREAD_ERROR_CHECK(ret,"mutex lock 1");
    printf("I got lock 1!\n");
    ret = pthread_mutex_lock(&mutex);
    THREAD_ERROR_CHECK(ret,"mutex lock 2");
    printf("I got lock 2!\n");
    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex);
    return 0;
}

