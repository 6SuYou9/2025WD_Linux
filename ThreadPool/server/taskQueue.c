#include "taskQueue.h"
#include <2025Linux.h>
#include <string.h>
int initTaskQueue(taskQueue_t *ptaskQueue){
    memset(ptaskQueue,0,sizeof(taskQueue_t));
    return 0;
}
int enQueue(taskQueue_t *ptaskQueue,int netfd){
    node_t *pNew = (node_t*)calloc(1,sizeof(node_t));
    pNew->netfd = netfd;
    if(ptaskQueue->queueSize==0){
        ptaskQueue->pFront = pNew;
        ptaskQueue->pRear = pNew;
    }else{
        ptaskQueue->pRear->pNext = pNew;
        ptaskQueue->pRear = pNew;
    }
    ptaskQueue->queueSize++;
    return 0;
}
int getFront(taskQueue_t *ptaskQueue){
    return ptaskQueue->pFront->netfd;
}   
int deQueue(taskQueue_t *ptaskQueue){
    node_t *pCur = ptaskQueue->pFront;
    ptaskQueue->pFront = ptaskQueue->pFront->pNext;
    if(ptaskQueue->queueSize==1){
        ptaskQueue->pRear = NULL;
    }
    free(pCur);
    ptaskQueue->queueSize--;
    return 0;
}
