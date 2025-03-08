#include <2025Linux.h>

// 先设计一个 返回值类型为void，有一个int参数的函数
void handler(int signum){
    printf("Hello SuYou,I am 2 signal.\n");
}

int main(int argc,char *argv[])
{
    signal(2,handler);  // &handler和handler是一样的,对于函数来说，和数组一样，作为参数传递时会退化为指针
    char buf[4096] = {0};
    ssize_t ret = read(STDIN_FILENO,buf,sizeof(buf));
    printf("ret = %ld, buf = %s\n",ret,buf);
    return 0;

}

