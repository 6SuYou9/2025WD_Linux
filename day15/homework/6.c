#include <2025Linux.h>

#define MAX_ITEMS 10  // 最大商品数量
#define INITIAL_ITEMS 8  // 初始商品数量

// 队列节点结构
typedef struct Node {
    int item;  // 商品编号
    struct Node* next;
} Node;

// 共享资源结构
typedef struct {
    Node* head;  // 队列头
    Node* tail;  // 队列尾
    int count;  // 当前商品数量
    pthread_mutex_t mutex;  // 互斥锁
    pthread_cond_t cond;  // 条件变量
} SharedQueue;

// 初始化共享队列
void initQueue(SharedQueue* queue) {
    queue->head = NULL;
    queue->tail = NULL;
    queue->count = 0;  // 初始化为0
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->cond, NULL);

    // 添加初始商品
    pthread_mutex_lock(&queue->mutex);
    for (int i = 0; i < INITIAL_ITEMS; i++) {
        int newItem = rand() % 100;
        enqueue(queue, newItem); 
    }
    // queue->count = INITIAL_ITEMS; // 或者依靠enqueue的count++
    pthread_mutex_unlock(&queue->mutex);
}

// 入队操作
void enqueue(SharedQueue* queue, int item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->item = item;
    newNode->next = NULL;

    if (queue->tail == NULL) {  // 队列为空
        queue->head = newNode;
        queue->tail = newNode;
    } else {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
    queue->count++;
}

// 出队操作
int dequeue(SharedQueue* queue) {
    int item;
    if (queue->head == NULL) {  // 队列为空
        return -1;  // 返回错误代码
    }
    Node* temp = queue->head;
    item = temp->item;
    queue->head = queue->head->next;
    if (queue->head == NULL) {  // 队列为空
        queue->tail = NULL;
    }
    free(temp);
    queue->count--;
    return item;
}

// 生产者线程函数
void* producer(void* arg) {
    SharedQueue* queue = (SharedQueue*)arg;
    while (1) {
        pthread_mutex_lock(&queue->mutex);
        while (queue->count >= MAX_ITEMS) {  // 队列已满
            pthread_cond_wait(&queue->cond, &queue->mutex);  // 等待消费者消费
        }
        int newItem = rand() % 100;  // 生成随机商品编号
        enqueue(queue, newItem);
        printf("Producer: Produced item %d, Total items: %d\n", newItem, queue->count);
        pthread_cond_signal(&queue->cond);  // 通知消费者
        pthread_mutex_unlock(&queue->mutex);
        sleep(3);  // 每3秒生产一个商品
    }
    return NULL;
}

// 消费者线程函数
void* consumer(void* arg) {
    SharedQueue* queue = (SharedQueue*)arg;
    sleep(5);  // 初始睡眠5秒
    while (1) {
        pthread_mutex_lock(&queue->mutex);
        while (queue->count == 0) {  // 队列为空
            pthread_cond_wait(&queue->cond, &queue->mutex);  // 等待生产者生产
        }
        int item = dequeue(queue);
        printf("Consumer: Consumed item %d, Total items: %d\n", item, queue->count);
        pthread_cond_signal(&queue->cond);  // 通知生产者
        pthread_mutex_unlock(&queue->mutex);
        sleep(1);  // 每1秒消费一个商品
    }
    return NULL;
}

int main() {
    srand(time(NULL));  // 初始化随机数种子
    SharedQueue queue;
    initQueue(&queue);

    pthread_t producers[3], consumers[2];

    // 创建生产者线程
    for (int i = 0; i < 3; i++) {
        pthread_create(&producers[i], NULL, producer, &queue);
    }

    // 创建消费者线程
    for (int i = 0; i < 2; i++) {
        pthread_create(&consumers[i], NULL, consumer, &queue);
    }

    // 等待线程结束（理论上不会结束）
    for (int i = 0; i < 3; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(consumers[i], NULL);
    }

    pthread_mutex_destroy(&queue.mutex);
    pthread_cond_destroy(&queue.cond);

    return 0;
}
