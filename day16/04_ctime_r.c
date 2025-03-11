#include <2025Linux.h>

void *threadFunc(void *){
    char buf[4096] = {0};
    time_t now = time(NULL);
    char *p =ctime_r(&now,buf);
    printf("Before p = %s\n",p);
    sleep(5);
    printf("After p = %s\n",p);
    pthread_exit(NULL);
}

int main(int argc,char *argv[])
{
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,NULL);
    sleep(2);
    char buf[4096] = {0};
    time_t now = time(NULL);
    char *p =ctime_r(&now,buf);
    printf("Main thread, p = %s\n",p);
    pthread_join(tid,NULL);
    return 0;
}

