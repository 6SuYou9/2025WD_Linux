#include <2025Linux.h>
#define NUM 10000000
int main(int argc,char *argv[])
{
    int shmid = shmget(IPC_PRIVATE,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    int *p = (int *)shmat(shmid,NULL,0);
    //*p = 0; // *p只访问了4个字节
    p[0] = 0;   // *(p+0) 等价于p[0]
    if(fork()){
        for(int i = 0;i < NUM;++i){
            ++p[0];
        }
        wait(NULL);
        printf("*p = %d\n",*p);
    }else{
        for(int i = 0;i < NUM;++i){
            ++p[0];
        }
    }
    return 0;
}

