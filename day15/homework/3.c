#include <2025Linux.h>
#include <bits/pthreadtypes.h>
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <sys/time.h>
#define NUM 20000000
int global = 0;
void *threadFunc(void *arg){
    pthread_mutex_t * pmutex = (pthread_mutex_t*)arg;
    pthread_mutex_lock(pmutex);
    for(int i=0;i<NUM;i++){
        global++;
    }
    pthread_mutex_unlock(pmutex);
    pthread_exit(NULL);
}

int main(int argc,char *argv[])
{
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex,NULL);    // 初始化锁
    pthread_t tid;
    struct timeval begtime,endtime;
    gettimeofday(&begtime,NULL);
    
    pthread_create(&tid,NULL,threadFunc,&mutex);
    
    pthread_mutex_lock(&mutex);
    for(int i=0;i<NUM;i++){
        global++;
    }
    pthread_mutex_unlock(&mutex);

    pthread_join(tid,NULL);
    gettimeofday(&endtime,NULL);
    printf("global = %d, total time = %ld us\n",global,(endtime.tv_sec-begtime.tv_sec)*1000*1000+endtime.tv_usec-begtime.tv_usec);
    return 0;
}

