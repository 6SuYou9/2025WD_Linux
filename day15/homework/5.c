#include <2025Linux.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
typedef struct shareRes{
    int flag1;      // 控制A-B
    int flag2;      // 控制B-C
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}shareRes;
void *threadFunc(void *arg){
    shareRes * psr = (shareRes *)arg;       // 取出传递的共享变量
    // 根据flag1 判断A是否输出
    pthread_mutex_lock(&psr->mutex);
    if(psr->flag1==0)
        pthread_cond_wait(&psr->cond,&psr->mutex);
    pthread_mutex_unlock(&psr->mutex);
    printf("B->");
    // B已经输出，修改flag2
    pthread_mutex_lock(&psr->mutex);
    psr->flag2 = 1;
    pthread_cond_signal(&psr->cond);
    pthread_mutex_unlock(&psr->mutex);
    pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    shareRes sr;
    sr.flag1 = 0;
    sr.flag2 = 0;
    pthread_mutex_init(&sr.mutex,NULL);
    pthread_cond_init(&sr.cond,NULL);

    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,&sr);

    // 输出A
    printf("A->");
    // A已经输出，修改flag1
    pthread_mutex_lock(&sr.mutex);
    sr.flag1 = 1;
    pthread_cond_signal(&sr.cond);
    pthread_mutex_unlock(&sr.mutex);
    
    pthread_mutex_lock(&sr.mutex);
    if(sr.flag2==0)
        pthread_cond_wait(&sr.cond,&sr.mutex);
    pthread_mutex_unlock(&sr.mutex);
    printf("C\n");


    return 0;
}

