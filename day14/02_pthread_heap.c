#include <2025Linux.h>

void *threadFunc(void *arg){
    // arg的数值就是传入的内容
    int *p = (int *)arg;    // void * 只能用来传递和保存指针的数值，不能解引用和偏移
    // 数据原来是什么类型，就还原成什么类型
    *p = 1001;
    printf("child, *p = %d, p = %p\n",*p,p);
    return NULL;
}

int main(int argc,char *argv[])
{
    int *p = (int *)malloc(sizeof(int));
    *p=1000;
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,p);  // p作为参数传给了子线程
    sleep(1);
    printf("main, *p = %d, p = %p\n",*p,p);
    return 0;
}

