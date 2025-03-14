#ifndef __HEAD_H__
#define __HEAD_H__
#include <2025Linux.h>  // <>是从系统目录/usr/include/下面找
#include "worker.h"     //""是从当前目录开始找
#include "taskQueue.h"
typedef struct threadPool_s{
    // 保存所有子线程的信息
    tidArr_t tidArr;
    // 任务队列
    taskQueue_t taskQueue;
    // 锁
    pthread_mutex_t mutex;
    // 条件变量
    pthread_cond_t cond;
}threadPool_t;
// 启动线程
int makeWorker(threadPool_t * pthreadPool);     // 这个函数参数依赖于这个结构体，放到worker.h会报错
#endif
