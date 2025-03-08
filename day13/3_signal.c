#include <2025Linux.h>
#include <signal.h>

// 先设计一个 返回值类型为void，有一个int参数的函数
void handler(int signum){
    printf("Hello SuYou,I am 2 signal.\n");
}

int main(int argc,char *argv[])
{
    sleep(5);
    printf("sleep over!\n");
    signal(2,handler);  // &handler和handler是一样的,对于函数来说，和数组一样，作为参数传递时会退化为指针
    while(1){
        printf("hehheh!\n");
        sleep(3);
    }
    return 0;
}

