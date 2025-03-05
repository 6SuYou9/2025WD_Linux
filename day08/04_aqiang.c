#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./05_aqiang 1.pipe 2.pipe
    ARGS_CHECK(argc,3);
    int fdr = open(argv[1],O_RDONLY);
    int fdw = open(argv[2],O_WRONLY);
    printf("aqiang is connected!\n");
    char buf[4096];
    while(1){
        // 读stdin的消息
        memset(buf,0,sizeof(buf));
        read(STDIN_FILENO,buf,sizeof(buf));
        write(fdw,buf,strlen(buf));
        // 读azhen的消息
        memset(buf,0,sizeof(buf));
        read(fdr,buf,sizeof(buf));
        printf("buf = %s\n",buf);
    }
    return 0;
}

