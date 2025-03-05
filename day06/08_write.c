#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./08_write file1
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_WRONLY|O_CREAT,0666);
    ERROR_CHECK(fd,-1,"open");
    printf("fd = %d\n",fd);
    ssize_t ret = write(fd,"howareyou",9);
    printf("ret = %ld\n",ret);
    return 0;
}

