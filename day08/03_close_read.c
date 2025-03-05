#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./03_close_read 1.pipe
    ARGS_CHECK(argc,2);
    int fdr = open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open");
    printf("fdr is opened!\n");
    close(fdr);
    printf("fdr over!\n");
    while(1){
        sleep(1);
    }
    return 0;
}

