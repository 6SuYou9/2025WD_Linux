#include <2025Linux.h>
#include <signal.h>

void handler(int signum){
    printf("signum = %d\n",signum);
}

int main(int argc,char *argv[])
{
    signal(SIGINT,handler);
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    sigprocmask(SIG_SETMASK,&set,NULL);
    sleep(5);
    sigset_t set2;
    sigpending(&set2);
    if(sigismember(&set2,SIGINT)){
        printf("SIGINT is in pengding!\n");
    }
    sigdelset(&set,SIGINT);
    sigprocmask(SIG_SETMASK,&set,NULL);
    while(1){
        sleep(1);
    }
    return 0;
}

