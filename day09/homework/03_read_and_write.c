#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./03_read_and_write 1.pipe
    ARGS_CHECK(argc,2);
    int fd1 = open(argv[1],O_RDWR);     // O_RDWR说明打开管道操作是非阻塞的
    int fd2 = open(argv[1],O_RDWR);
    printf("pipe is opened!\n");
    fd_set wrset;   // 监听写操作
    fd_set rdset;   // 监听读操作
    int cnt = 0;
    char buf[4096] = {0};
    while(1){
        FD_ZERO(&wrset);
        FD_ZERO(&rdset);
        FD_SET(fd1,&wrset);
        FD_SET(fd2,&rdset);
        int ret = select(fd2+1,&rdset,&wrset,NULL,NULL);    // 返回就绪资源的数量
        if(FD_ISSET(fd2,&rdset)){
            // 先看fd2是否可读
            read(fd1,buf,1024);
            printf("read ready,cnt = %d,ret = %d\n",cnt++,ret);
        }
        if(FD_ISSET(fd1,&wrset)){
            // 先看fd1是否可写
            write(fd1,buf,4096);
            printf("write ready,cnt = %d,ret = %d\n",cnt++,ret);    
        }
        sleep(1);
    }
    return 0;
}

