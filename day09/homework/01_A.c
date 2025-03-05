#include <2025Linux.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
    // ./01_A 1.pipe file1
    ARGS_CHECK(argc,3);
    int pipefdw = open(argv[1],O_WRONLY);
    ERROR_CHECK(pipefdw,-1,"open pipe");
    // 读取文件的内容
    int filefdr = open(argv[2],O_RDONLY);
    ERROR_CHECK(filefdr,-1,"open file");
    char buf[4096] = {0};
    ssize_t ret = read(filefdr,buf,sizeof(buf));
    // 发送文件名
    int length = strlen(argv[2]);
    write(pipefdw,&length,sizeof(int)); // 先发四个字节长度
    write(pipefdw,argv[2],length); // 再发length个字节的文件名内容
    // 发送文件的长度
    length = sizeof(ret);
    write(pipefdw,&length, sizeof(length)); // 添加换行符作为分隔符
    write(pipefdw,&ret,length);
    // 发送文件的内容
    length = ret;
    write(pipefdw,&length,sizeof(length));
    write(pipefdw,buf,length);
    return 0;
}

