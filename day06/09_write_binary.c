#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./09_write_binary file1
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    
    int i = 1000000;    // 因为写入的数据不是字符串，所以这是一个二进制文件
    write(fd,&i,sizeof(int));   // 二进制文件用sizeof
    close(fd);
    return 0;
}

