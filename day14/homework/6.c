#include <2025Linux.h>

// 线程函数
void *threadFunc(void *arg) {
    //sleep(2);
    int **pVal = (int **)arg;
    printf("Thread: *pVal = %d\n", **pVal);  // 访问堆内存
    free(*pVal);  // 释放堆内存
    return NULL;
}

int main() {
    // 在堆上分配内存
    int *val = malloc(sizeof(int));
    if (!val) {
        perror("malloc failed");
        return 1;
    }
    *val = 1000;

    // 创建线程
    pthread_t tid;
    if (pthread_create(&tid, NULL, threadFunc, &val) != 0) {
        perror("pthread_create failed");
        free(val);
        return 1;
    }
    
    // 主线程访问堆内存
    printf("Main: *val = %d\n", *val);
    //sleep(2);
    free(val);  // 主线程释放堆内存

    // 等待线程结束
    pthread_join(tid, NULL);

    return 0;
}
