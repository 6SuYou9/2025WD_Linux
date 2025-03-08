#include <2025Linux.h>

// 先设计一个 返回值类型为void，有一个int参数的函数
void handler(int signum){
    printf("signum = %d\n",signum);
}

int main(int argc,char *argv[])
{
    signal(SIGINT,handler);
    signal(SIGQUIT,handler);  // &handler和handler是一样的,对于函数来说，和数组一样，作为参数传递时会退化为指针
    while(1){
        sleep(1);
    }
    return 0;
}

