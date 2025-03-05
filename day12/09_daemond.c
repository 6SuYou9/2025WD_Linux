#include <2025Linux.h>
#define FD_MAX 1024
void Daemon(){
    if(fork()){
        exit(0);
    }
    // 父进程终止，子进程继续运行
    setsid();
    for(int i = 0 ;i < FD_MAX;++i){
        close(i);
    }// 关闭所有的外界设备
    chdir("/");    // 把和启动环境相关的属性都重置掉
    umask(0);
}

int main(int argc,char *argv[])
{
    Daemon();   // 调用完Daemon之后就只剩一个子进程在运行了
    for(int i = 0;i < 20;++i){
        // printf("i = %d\n",i); 守护进程不能使用printf，一般是打印到文件里面
        syslog(LOG_INFO,"I am daemon, i = %d\n",i);
        sleep(2);
    }
    return 0;
}

