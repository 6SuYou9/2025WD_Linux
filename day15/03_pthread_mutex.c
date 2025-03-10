#include <2025Linux.h>
#define NUM 10000000
typedef struct shareResource_s{
    int count;
    pthread_mutex_t mutex;
} shareResource_t;
void *threadFunc(void *arg){
    shareResource_t * pshareRes = (shareResource_t *)arg;       // 原来是什么类型就转成什么类型
    for(int i=0;i<NUM;i++){
        pthread_mutex_lock(&pshareRes->mutex);
        ++pshareRes->count;
        pthread_mutex_unlock(&pshareRes->mutex);
    }
    pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    shareResource_t shareRes;   // 在main的栈帧中，申请了内存
    shareRes.count = 0;
    pthread_mutex_init(&shareRes.mutex,NULL);   // 对锁进行初始化
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,&shareRes); // 把count和mutex都共享给了子线程
    for(int i =0;i<NUM;i++){
        pthread_mutex_lock(&shareRes.mutex);
        shareRes.count++;
        pthread_mutex_unlock(&shareRes.mutex);
    }
    pthread_join(tid,NULL);
    printf("count = %d\n",shareRes.count);
    return 0;
}

