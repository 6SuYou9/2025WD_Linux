#include <2025Linux.h>
#include <sys/shm.h>

int main(int argc,char *argv[])
{
    int shmid = shmget(0x6666,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    char *p = (char *)shmat(shmid,NULL,0);
    strcpy(p,"How are you");
    printf("sleep over!\n");
    shmdt(p);
    return 0;
}

