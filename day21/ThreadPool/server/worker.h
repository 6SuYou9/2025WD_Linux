#ifndef __WORKER_H__
#define __WORKER_H__
#include <2025Linux.h>
typedef struct tidArr_s{    // 动态数组，保存所有子线程的tid
    pthread_t *arr;
    int workerNum;
}tidArr_t;
// 初始化动态数组
int tidArrInit(tidArr_t * tidArr,int workerNum);
// 线程入口函数
void *threadFunc(void *arg);
#endif
