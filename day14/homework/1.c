#include <2025Linux.h>
void *threadFunc(void *arg){
    long id = (long)arg;
    printf("I am %ld child\n",id);
    //pthread_exit(0);
}

int main(int argc,char *argv[])
{
    pthread_t tid1,tid2,tid3;
    pthread_create(&tid1,NULL,threadFunc,(void*)1);
    pthread_create(&tid2,NULL,threadFunc,(void*)2);
    pthread_create(&tid3,NULL,threadFunc,(void*)3);
    void *ret;
    pthread_join(tid1,&ret);
    printf("1 child ret = %ld\n",(long)ret);
    pthread_join(tid2,&ret);
    printf("2 child ret = %ld\n",(long)ret);
    pthread_join(tid3,&ret);
    printf("3 child ret = %ld\n",(long)ret);
    return 0;
}

