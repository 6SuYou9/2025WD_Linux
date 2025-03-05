#include <2025Linux.h>

int main(int argc,char *argv[])
{
    if(fork()){
        printf("I am parent.pid = %d,ppid = %d\n",getpid(),getppid());
        //wait(NULL);
    }else{
        printf("I am child.pid = %d,ppid = %d\n",getpid(),getppid());
    }
    return 0;
}

