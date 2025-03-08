#include <2025Linux.h>
void *threadFunc(void *arg){
    //return NULL;
    pthread_exit(NULL);
    printf("Can you see me?\n");
}
int main(int argc,char *argv[])
{
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,NULL);
    while(1){
        sleep(1);
    }
    return 0;
}

