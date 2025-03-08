#include <2025Linux.h>
void handler(int signum){
    printf("signum = %d\n",signum);
    time_t now = time(NULL);
    printf("now = %s\n",ctime(&now));
}
int main(int argc,char *argv[])
{
    signal(SIGALRM,handler);
    handler(0);     // 可以主动调用handler
    alarm(10);      // 安排一个10秒之后的SIGALRM信号产生
    pause();
    printf("Atert pause!\n");
    return 0;
}

