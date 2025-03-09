#include <2025Linux.h>

void handler(int signum){
    printf("signum = %d\n",signum);
}

int main(int argc,char *argv[])
{
    signal(SIGINT,handler);
    sigset_t set,oldset;
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    sigprocmask(SIG_BLOCK,&set,&oldset);
    sleep(5);
    sigset_t pendingset;
    sigpending(&pendingset);
    if(sigismember(&pendingset,SIGINT)){
        printf("SIGINT is in pengding!\n");
	}else{
        printf("SIGINT is not in pengding!\n");
	}
    sigprocmask(SIG_SETMASK,&oldset,NULL);
    while(1){
        sleep(1);
    }
    return 0;
}
