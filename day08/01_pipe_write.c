#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./01_pipe_write 1.pipe
    ARGS_CHECK(argc,2);
    int fdw = open(argv[1],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open");
    printf("fdw is opened!\n");
    write(fdw,"hello SuYou",11);
    printf("write over!\n");
    while(1){
        sleep(1);
    }
    return 0;
}

