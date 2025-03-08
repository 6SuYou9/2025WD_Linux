#include <2025Linux.h>

void handler(int signum){
    printf("signum = %d\n",signum);
}

int main(int argc,char *argv[])
{
    signal(SIGINT,handler);    
    sigset_t set,oldset;
    sigemptyset(&set);      // 清空集合
    sigaddset(&set,SIGINT); // set当中有SIGINT
    sigprocmask(SIG_BLOCK,&set,&oldset);    // 新增SIGINT屏蔽，将原来的mask存入oldset中
    
    sleep(10);
    printf("sleep over!\n");

    sigprocmask(SIG_SETMASK,&oldset,NULL);  // 恢复原来的屏蔽字

    while(1){
        sleep(1);
    }
    
    return 0;
}

