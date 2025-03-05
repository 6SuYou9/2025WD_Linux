#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./09_read_binary file1
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    
    // 怎么写就按同样的方法读
    int data;   // 写入是int 读取就用int
    read(fd,&data,sizeof(int));
    printf("data = %d\n",data);
    close(fd);
    return 0;
}

