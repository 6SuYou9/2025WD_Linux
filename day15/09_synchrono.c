#include <2025Linux.h>
typedef struct shareResource_s{
    int flag;   // flag = 0 A没做完， =1 A做完了
    pthread_mutex_t mutex;
}shareResource_t;
void A(){
    printf("before A\n");
    sleep(2);
    printf("after A\n");
}
void B(){
    printf("before B\n");
    sleep(2);
    printf("after B\n");
}
void *threadFunc(void *arg){
    shareResource_t * pshareRes = (shareResource_t *)arg;
    while(1){
        pthread_mutex_lock(&pshareRes->mutex);
        if(pshareRes->flag==1){
            pthread_mutex_unlock(&pshareRes->mutex);
            break;      // 除非后续代码要带锁运行，否则记得解锁
        }
        pthread_mutex_unlock(&pshareRes->mutex);
    }
    B();
    pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    shareResource_t shareRes;
    shareRes.flag = 0;
    pthread_mutex_init(&shareRes.mutex,NULL);   // 创建共享资源并初始化

    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,&shareRes);  // 创建子线程
    
    A();
    pthread_mutex_lock(&shareRes.mutex);
    shareRes.flag = 1;
    pthread_mutex_unlock(&shareRes.mutex);

    pthread_join(tid,NULL);
    return 0;
}

