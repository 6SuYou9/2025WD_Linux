#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./02_close_read 1.pipe
    ARGS_CHECK(argc,2);
    int fdr = open(argv[1],O_RDONLY);
    ERROR_CHECK(fdr,-1,"open");
    printf("fdr is opened!\n");
    sleep(3);
    printf("sleep over!\n");
    char buf[1024] = {0};
    ssize_t ret = read(fdr,buf,sizeof(buf));
    printf("ret = %ld, buf = %s\n",ret,buf);
    return 0;
}

