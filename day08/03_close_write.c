#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./03_close_write 1.pipe
    ARGS_CHECK(argc,2);
    int fdw = open(argv[1],O_WRONLY);
    ERROR_CHECK(fdw,-1,"open");
    printf("fdw is opened!\n");
    sleep(3);
    printf("sleep over!\n");
    write(fdw,"Hello SuYou",11);
    printf("write over!\n");
    close(fdw);
    return 0;
}

