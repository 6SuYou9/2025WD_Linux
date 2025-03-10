#include <2025Linux.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>

void freep1(void *p1){
    printf("p1 is free!\n");
    free(p1);
}

void freep2(void *p2){
    printf("p2 is free!\n");
    free(p2);
}
void closefd3(void *pfd){   // pfd <-- &fd3
    printf("fd3 is closed!\n");
    close(*(int *)pfd);     // 先从void * --> int * 然后再解引用

}

void *threadFunc(void *arg){
    int *p1 = (int *)malloc(4);
    pthread_cleanup_push(freep1,p1);    // 申请资源之后要先压栈
    int *p2 = (int *)malloc(4);
    pthread_cleanup_push(freep2,p2);    // 申请资源之后要先压栈
    int fd3 = open("file",O_RDWR|O_CREAT,0666);
    pthread_cleanup_push(closefd3,&fd3);    // 申请资源之后要先压栈
    pthread_cleanup_pop(1);         // pop里面的参数先写一个正整数
    pthread_cleanup_pop(1);         // pop里面的参数先写一个正整数
    printf("-----------------------------------------------\n");
    pthread_exit(NULL);
    pthread_cleanup_pop(1);         // pop里面的参数先写一个正整数
    // pop函数执行的时候，会调用一次清理，所以我们就不用写清理的代码了
}
int main(int argc,char *argv[])
{
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,NULL);
    void *ret;
    pthread_join(tid,&ret);
    printf("ret = %ld\n",(long)ret);
    return 0;
}

