#include <2025Linux.h>

int main(int argc,char *argv[])
{
    int shmid = shmget(0x6666,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    char *p = shmat(shmid,NULL,0);
    printf("data = %s\n",p);
    shmdt(p);
    return 0;
}

