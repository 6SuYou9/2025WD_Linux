#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__
typedef struct node_s{
    int netfd;  // 子线程需要执行任务，和客户端通信，所以需要一个netfd
    struct node_s *pNext;
}node_t;
typedef struct taskQueue_s{
    node_t * pFront;
    node_t * pRear;
    int queueSize;
}taskQueue_t;
int initTaskQueue(taskQueue_t *ptaskQueue);
int enQueue(taskQueue_t *ptaskQueue,int netfd);
int getFront(taskQueue_t *ptaskQueue);
int deQueue(taskQueue_t *ptaskQueue);
#endif
