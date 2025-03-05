#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./01_fork_open file
    ARGS_CHECK(argc,2);
    if(fork()){
        int fd = open(argv[1],O_RDWR);
        ERROR_CHECK(fd,-1,"open");
        sleep(1);
        write(fd,"suyou",5);
    }else{
        int fd = open(argv[1],O_RDWR);
        ERROR_CHECK(fd,-1,"open");
        write(fd,"hello",5);
    }
    return 0;
}

