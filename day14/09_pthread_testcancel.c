#include <2025Linux.h>
void *threadFunc(void *arg){
    while(1){
        pthread_testcancel();
    }
    pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,NULL);
    sleep(2);
    printf("sned cancellation request!\n");
    pthread_cancel(tid);
    void *ret;
    pthread_join(tid,&ret);
    printf("child is terminated. ret = %ld\n",(long) ret);
    return 0;
}

