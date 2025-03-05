#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./02_block_read 1.pipe
    ARGS_CHECK(argc,2);
    int fdr = open(argv[1],O_RDONLY);
    sleep(5);
    printf("Sleep over!\n");
    char buf[4096];
    while(1)
    {
        read(fdr,buf,sizeof(buf));
        // 本例子中不关心读到的内容，只关心读操作本身
        printf("read one\n");
        sleep(2);
    }
    return 0;
}

