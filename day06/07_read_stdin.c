#include <2025Linux.h>
#include <stdio.h>

int main(int argc,char *argv[])
{
    char buf[1024] = {0};
    ssize_t ret = read(0,buf,sizeof(buf));      // 没有写-1
    ERROR_CHECK(ret,-1,"read");
    printf("ret = %ld, buf = %s\n",ret,buf);
    return 0;
}

