#include <2025Linux.h>
#include <pthread.h>
void *threadFunc(void *arg){
    pthread_exit((void *)123);
}
int main(int argc,char *argv[])
{
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,NULL);
    void *ret;  // 将要保存子线程的返回值
    pthread_join(tid,&ret); // tid没有指针，&ret是二级指针
    printf("ret = %ld\n",(long)ret);    // void * --> long
    return 0;
}

