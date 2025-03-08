#include <2025Linux.h>
void *threadFunc(void *arg){
    while(1){
        sleep(1);   // 不想让子线程占用cpu
    }
}

int main(int argc,char *argv[])
{
    int cnt = 0;
    while(1){
        pthread_t tid;
        int ret = pthread_create(&tid,NULL,threadFunc,NULL);
        THREAD_ERROR_CHECK(ret,"pthread_create");
        if(ret!=0){
            printf("cnt = %d\n",cnt);
            break;
        }
        ++cnt;
    }
    return 0;
}

