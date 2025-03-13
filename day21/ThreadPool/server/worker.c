#include "worker.h"
#include "head.h"
int tidArrInit(tidArr_t * tidArr,int workerNum){
    // 申请堆内存，保存所有的pthread_t
    tidArr->arr = (pthread_t*)calloc(workerNum,sizeof(pthread_t));
    tidArr->workerNum = workerNum;
    return 0;
}
int makeWorker(threadPool_t * pthreadPool){
    for(int i =0;i<pthreadPool->tidArr.workerNum;i++){
        // 线程在创建子线程时，干脆把所有信息都传过去
        pthread_create(&pthreadPool->tidArr.arr[i],NULL,
                       threadFunc,NULL);
    }
}
void *threadFunc(void *arg){
    threadPool_t * pthreadPool = (threadPool_t *)arg;
    while(1){
        // do sth
        sleep(1);   // 先用sleep占位
    }
}
