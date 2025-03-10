#include <2025Linux.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
#define TIMES 10000000
int global = 1;

void *threadFunc(void *arg){
    for(int i=0;i<TIMES;i++){
        global++;
    }
}
int main(int argc,char *argv[])
{
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,threadFunc,NULL);
    pthread_create(&tid2,NULL,threadFunc,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    printf("global = %d\n",global);
    return 0;
}

