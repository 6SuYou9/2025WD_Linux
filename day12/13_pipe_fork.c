#include <2025Linux.h>

int main(int argc,char *argv[])
{
    int fds1[2];    // 1号 父亲发消息给孩子
    int fds2[2];    // 2号 孩子发消息给父亲
    pipe(fds1);
    pipe(fds2);
    if(fork()){
        // 父进程
        close(fds1[0]);     // 关闭父亲1号的读端
        close(fds2[1]);     // 关闭父亲2号的写端
        sleep(5);
        // 父-->子
        write(fds1[1],"Hello",5);
        printf("write over!\n");
        // 子-->父
        char buf[4096] = {0};
        read(fds2[0],buf,sizeof(buf));
        printf("child send father buf = %s\n",buf);
    }else{
        // 子进程
        close(fds1[1]);     // 关闭孩子1号的写端
        close(fds2[0]);     // 关闭孩子2号的读端
        // 父-->子
        char buf[4096] = {0};
        read(fds1[0],buf,sizeof(buf));
        printf("father send child buf = %s\n",buf);
        // 子-->父
        write(fds2[1],"SuYou",5);
    }
    return 0;
}

