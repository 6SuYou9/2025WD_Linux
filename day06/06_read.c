#include <2025Linux.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
    // ./05_open file1
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    printf("fd = %d\n",fd);
    ssize_t ret;
    char buf[6] = {0};
    ret = read(fd,buf,sizeof(buf)-1);
    printf("1 ret = %ld,buf = %s\n",ret,buf);
    memset(buf,0,sizeof(buf));
    ret = read(fd,buf,sizeof(buf)-1);
    printf("2 ret = %ld,buf = %s\n",ret,buf);
    memset(buf,0,sizeof(buf));
    ret = read(fd,buf,sizeof(buf)-1);
    printf("3 ret = %ld,buf = %s\n",ret,buf);
    memset(buf,0,sizeof(buf));
    ret = read(fd,buf,sizeof(buf)-1);
    printf("4 ret = %ld,buf = %s\n",ret,buf);
    return 0;
}

