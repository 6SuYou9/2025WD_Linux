#include <2025Linux.h>
#define NUM 10000000
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *threadFunc(void *arg){
    pthread_mutex_lock(&mutex);
    pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,NULL);
    sleep(1);
    pthread_mutex_lock(&mutex);
    printf("I got lock\n");
    pthread_join(tid,NULL);
    pthread_mutex_unlock(&mutex);
    return 0;
}

