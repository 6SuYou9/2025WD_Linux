#include <2025Linux.h>

void *threadFunc(void *arg){
    long data = (long)arg;   
    printf("child, data = %ld\n",data);
    return NULL;
}

int main(int argc,char *argv[])
{
    long data = 1001;
    pthread_t tid1,tid2,tid3;
    pthread_create(&tid1,NULL,threadFunc,(void *)data);
    ++data;
    pthread_create(&tid2,NULL,threadFunc,(void *)data);
    ++data;
    pthread_create(&tid3,NULL,threadFunc,(void *)data);
    sleep(1);
    return 0;
}

