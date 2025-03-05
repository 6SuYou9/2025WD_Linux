#include <2025Linux.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
    // ./05_open file1
    ARGS_CHECK(argc,2);
    // int fd = open(argv[1],O_RDONLY);
    // int fd = open(argv[1],O_RDONLY|O_CREAT,0666);
    int fd = open(argv[1],O_RDONLY|O_CREAT|O_EXCL,0666);
    ERROR_CHECK(fd,-1,"open");
    printf("fd = %d\n",fd);
    return 0;
}

