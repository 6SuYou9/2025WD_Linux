#include <2025Linux.h>
int global = 1234;
void * threadFunc(void *arg){
    printf("child, global = %d, &global = %p\n",global,&global);
    return NULL;
}
int main(int argc,char *argv[])
{
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,NULL);
    sleep(1);
    printf("main, global = %d, &global = %p\n",global,&global);
    return 0;
}

