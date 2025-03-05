#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./06_redirect1 file
    ARGS_CHECK(argc,2);
    printf("You can see me!\n");
    // 先关闭一个文件描述符
    close(STDOUT_FILENO);   // STDOUT_FILENO就是数字1

    // 再打开一个文件描述符
    int fd = open(argv[1],O_WRONLY);
    ERROR_CHECK(fd,-1,"open");
    printf("fd = %d\n",fd);
    printf("You can't see me!\n");

    return 0;
}

