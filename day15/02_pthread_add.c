#include <2025Linux.h>
#define NUM 10000000
void *threadFunc(void *arg){
    int *pcount = (int *)arg;
    for(int i=0;i<NUM;i++){
        ++*pcount;
    }
    pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    int count = 0;
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,&count);
    for(int i =0;i<NUM;i++){
        count++;
    }
    pthread_join(tid,NULL);
    printf("count = %d\n",count);
    return 0;
}

