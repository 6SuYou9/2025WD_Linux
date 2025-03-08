#include <2025Linux.h>
#include <bits/types/sigset_t.h>
#include <signal.h>
void handler(int signum){
    sigset_t set;
    sigpending(&set);
    if(sigismember(&set,SIGINT)){
        printf("SIGINT is in pending set!\n");
    }
    printf("signum = %d\n",signum);
    sleep(3);
}

int main(int argc,char *argv[])
{
    signal(SIGINT,handler);    
    while(1){
        sleep(1);
    }
    return 0;
}

