#include <2025Linux.h>

int main(int argc,char *argv[])
{
    if(fork()){
        printf("I am parent,pid = %d, pgid = %d\n",getpid(),getpgid(0));
        wait(NULL);
    }else{
        printf("Before setpgid I am child,pid = %d, pgid = %d\n",getpid(),getpgid(0));
        setpgid(0,0);
        printf("After setpgid I am child,pid = %d, pgid = %d\n",getpid(),getpgid(0));
    }
    return 0;
}

