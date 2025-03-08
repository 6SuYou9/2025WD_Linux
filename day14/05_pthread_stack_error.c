#include <2025Linux.h>

void *threadFunc(void *arg){
    int *pdata = (int *)arg;   
    ++*pdata;
    printf("child, *pdata = %d,pdata = %p\n",*pdata,pdata);
    return NULL;
}
void func(){
    int data = 1000;
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,&data);  // &data 是int *类型
}

int main(int argc,char *argv[])
{
    func();
    sleep(1);
    return 0;
}

