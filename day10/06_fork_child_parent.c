#include <2025Linux.h>

int main(int argc,char *argv[])
{
    pid_t ret = fork();
    if(ret!=0){
        printf("I am parent.ret = %d,pid = %d,ppid = %d\n",ret,getpid(),getppid());
        sleep(1);
    }else{
        printf("I am child.ret = %d,pid = %d,ppid = %d\n",ret,getpid(),getppid());
        sleep(1);
    }
    return 0;
}

