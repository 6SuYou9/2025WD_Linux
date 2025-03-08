#include <2025Linux.h>

void *threadFunc(void *arg){
    printf("I am child thread!\n"); // 子线程
    return NULL;
}

int main(int argc,char *argv[])
{
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    printf("I am main thread!\n");  // 主线程
    usleep(2);
    return 0;
}

