#include <2025Linux.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
    // ./09_pipe_open_read 1.pipe
    ARGS_CHECK(argc,2);
    int fdr = open(argv[1],O_RDONLY);   // O_RDONLY只读
    ERROR_CHECK(fdr,-1,"open");
    printf("fdr is opened!\n");
    char buf[1024] = {0};
    ssize_t ret = read(fdr,buf,sizeof(buf));
    printf("ret = %ld, buf = %s\n",ret,buf);
    return 0;
}

