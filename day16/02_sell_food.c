#include <2025Linux.h>
#include <pthread.h>
typedef struct shareResource_s{
    int flag;       // 0 没有饭 1 有黄焖鸡  2 有猪脚饭
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}shareResource_t;
void *huangmenji(void *arg){
    shareResource_t * pshareRes = (shareResource_t *)arg;
    pthread_mutex_lock(&pshareRes->mutex);
    while(pshareRes->flag!=1){  // 存在虚假唤醒的可能性
        printf("Before wait, huangmengji is not ready!\n");
        pthread_cond_wait(&pshareRes->cond,&pshareRes->mutex);
    }
    printf("huangmenji is ready!\n");
    pshareRes->flag = 0;
    pthread_mutex_unlock(&pshareRes->mutex);
    pthread_exit(NULL);

}
void *zhujiaofan(void *arg){
    shareResource_t * pshareRes = (shareResource_t *)arg;
    pthread_mutex_lock(&pshareRes->mutex);
    while(pshareRes->flag!=2){  // 存在虚假唤醒的可能性
        printf("Before wait, zhujiaofan is not ready!\n");
        pthread_cond_wait(&pshareRes->cond,&pshareRes->mutex);
    }
    printf("zhujiaofan is ready!\n");
    pshareRes->flag = 0;
    pthread_mutex_unlock(&pshareRes->mutex);
    pthread_exit(NULL);

}
int main(int argc,char *argv[])
{
    shareResource_t shareRes;
    shareRes.flag = 0;
    pthread_mutex_init(&shareRes.mutex,NULL);
    pthread_cond_init(&shareRes.cond,NULL);
    
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,huangmenji,&shareRes);
    pthread_create(&tid2,NULL,zhujiaofan,&shareRes);

    // 主线程做好一份饭，通知所有人
    while(1){
        int i;
        scanf("%d",&i);
        printf("I produce %d\n",i);
        pthread_mutex_lock(&shareRes.mutex);
        shareRes.flag=i;
        // 通知所有人
        pthread_cond_broadcast(&shareRes.cond);
        pthread_mutex_unlock(&shareRes.mutex);
    }

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    
    return 0;
}

