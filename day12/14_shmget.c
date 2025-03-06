#include <2025Linux.h>

int main(int argc,char *argv[])
{
    int shmid = shmget(0x1234,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    return 0;
}

