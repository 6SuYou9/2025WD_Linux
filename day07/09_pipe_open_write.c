#include <2025Linux.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    // ./09_pipe_open_write.c 1.pipe
    ARGS_CHECK(argc,2);
    int fdw = open(argv[1],O_WRONLY);   // O_RDONLY只读
    ERROR_CHECK(fdw,-1,"open");
    printf("fdw is opened!\n");
    while(1){
        sleep(1);   // 写端不写入，也不退出，先永久阻塞
    }
    return 0;
}

