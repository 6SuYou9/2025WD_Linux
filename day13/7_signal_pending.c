#include <2025Linux.h>
void handler(int signum){
    printf("before,signum = %d\n",signum);
    sleep(5);
    // 在handler睡醒后，看一下pending里面有没有数据
    sigset_t sigset;
    sigpending(&sigset);
    if(sigismember(&sigset,SIGINT)){
        printf("SIGINT in pending set!\n");
    }else{
        printf("SIGINT out of pending set!\n");
    }
    printf("after,signum = %d\n",signum);
}

int main(int argc,char *argv[])
{
    signal(SIGINT,handler);    
    while(1){
        sleep(1);
    }
    return 0;
}

