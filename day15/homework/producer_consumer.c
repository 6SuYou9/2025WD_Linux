#include <2025Linux.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>

typedef struct node_s{
    int num;
    struct node_s *pNext;
} node_t;

typedef struct queue_s {
    node_t * pFront;
    node_t * pRear;
    int size;
}queue_t; // 链式队列

typedef struct shareResource_s {
    queue_t queue;  // 队列里面的长度信息，起到flag的作用
    pthread_mutex_t mutex;
    pthread_cond_t cond1;   // 生产者等待
    pthread_cond_t cond2;   // 消费者等待
} shareResource_t;

int initQueue(queue_t * pqueue){
    memset(pqueue,0,sizeof(queue_t));
    return 0;   // 返回 int 的意义是可能会有报错
}
// 入队——尾插法
int enQueue(queue_t *pqueue,int num){
    node_t * pNew = (node_t *)calloc(1,sizeof(node_t));
    pNew->num = num;
    if(pqueue->size==0){
        pqueue->pFront = pNew;
        pqueue->pRear = pNew;
    }else{
        pqueue->pRear->pNext = pNew;
        pqueue->pRear = pNew;
    }
    ++pqueue->size;
    return 0;
}
// 出队，头部删除法
int deQueue(queue_t *pqueue){
    // 用户不会在链表为空时做删除
    node_t * pCur = pqueue->pFront;
    pqueue->pFront = pCur->pNext;
    free(pCur);
    // 如果删除完以后没有结点了，pRear的指向也要变
    if(pqueue->pFront==NULL){
        pqueue->pRear = NULL;
    }
    --pqueue->size;
    return 0;
}

// 打印队列
int printQueue(queue_t *pqueue){
    node_t * pCur = pqueue->pFront;
    while(pCur!=NULL){
        printf("%4d",pCur->num);
        pCur = pCur->pNext;
    }
    printf("\n");
    return 0;
} 

// 设计一个临时的main函数，不完成业务，只是为了测试已经完成的部分功能
// 单元测试
//int main(int argc,char *argv[])
//{
//    queue_t Q;
//    initQueue(&Q);
//    printf("after init:");
//    printQueue(&Q);
//    for(int i=0;i<10;i++){
//        int num = rand()%1000;
//        enQueue(&Q,num);
//        printf("after enQueue,num = %d, size = %d,",num,Q.size);
//        printQueue(&Q);
//    }
//    printf("--------------------------------------------------\n");
//    for(int i=0;i<9;i++){
//        deQueue(&Q);
//        printf("after deQueue,size = %d,",Q.size);
//        printQueue(&Q);
//    }
//    return 0;
//}
void *producer(void *arg){
    shareResource_t * pshareRes = (shareResource_t *)arg;
    while(1){
        pthread_mutex_lock(&pshareRes->mutex);
        if(pshareRes->queue.size>=10){  // 当商品个数大于10时要等在cond1
            pthread_cond_wait(&pshareRes->cond1,&pshareRes->mutex);
        }
        int num = rand()%1000;
        printf("before produce,num = %d, size = %d ",num,pshareRes->queue.size);
        printQueue(&pshareRes->queue);
        enQueue(&pshareRes->queue,num);
        pthread_mutex_unlock(&pshareRes->mutex);
        printf("after produce,num = %d, size = %d ",num,pshareRes->queue.size);
        printQueue(&pshareRes->queue);
        // 生产者生成完成以后，唤醒消费者
        pthread_cond_signal(&pshareRes->cond2);
        pthread_mutex_unlock(&pshareRes->mutex);
        sleep(3);
    }
}

void *consumer(void *arg){
    shareResource_t * pshareRes = (shareResource_t *)arg;
    sleep(5);
    while(1){
        pthread_mutex_lock(&pshareRes->mutex);
        if(pshareRes->queue.size<=0){   // 当商品个数小于0时要等在cond2
            pthread_cond_wait(&pshareRes->cond2,&pshareRes->mutex);
        }
        printf("before consume, size = %d, front = %d ",pshareRes->queue.size,pshareRes->queue.pFront->num);
        printQueue(&pshareRes->queue);
        deQueue(&pshareRes->queue);
        printf("after consume, size = %d ",pshareRes->queue.size);
        printQueue(&pshareRes->queue);
        // 消费者消费完成后要唤醒生产者
        pthread_cond_signal(&pshareRes->cond1);
        pthread_mutex_unlock(&pshareRes->mutex);
        sleep(1);
    }
}
int main(){
    // 准备好共享资源&初始化
    shareResource_t shareRes;
    initQueue(&shareRes.queue);
    pthread_mutex_init(&shareRes.mutex,NULL);
    pthread_cond_init(&shareRes.cond1,NULL);
    pthread_cond_init(&shareRes.cond2,NULL);
    // 准备最初的八个商品
    int num;
    for(int i=0;i<8;i++){
        num = rand()%1000;
        enQueue(&shareRes.queue,num);
        printf("after enQueue,num = %d, size = %d ",num,shareRes.queue.size);
        printQueue(&shareRes.queue);
    }
    printf("------------------------------------------------\n");
    // 启动生产者消费者
    pthread_t producers[3],consumers[2];
    for(int i=0;i<3;i++){
        pthread_create(&producers[i],NULL,producer,&shareRes);
    }
    for(int i=0;i<2;i++){
        pthread_create(&consumers[i],NULL,consumer,&shareRes);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(consumers[i], NULL);
    }
        
}






