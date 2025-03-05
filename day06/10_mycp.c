#include <2025Linux.h>
#include <complex.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    // ./10_mycp src dest
    ARGS_CHECK(argc,3);
    int fdr = open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open fdr");
    int fdw = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(fdw,-1,"open fdw");
    
    char buf[1024] = {0}; // src有可能是文本，也有可能是二进制的
    // 这个char数组不是字符串的意思，因为char的大小是1，方便控制申请内存的大小
    ssize_t ret = read(fdr,buf,sizeof(buf));  // 这里sizeof(buf)不用-1，因为buf就不是字符串
    write(fdw,buf,ret);     // ret 是上次read的数量，无论二进制还是文本都适用
    
    close(fdw); // 释放资源的顺序通常是后进先出
    close(fdr);
    return 0;
}

