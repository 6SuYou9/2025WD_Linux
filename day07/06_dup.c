#include <2025Linux.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    // ./06_dup file
    ARGS_CHECK(argc,2);
    int oldfd = open(argv[1],O_RDWR);
    ERROR_CHECK(oldfd,-1,"open");
    printf("oldfd = %d\n",oldfd);
    int newfd = dup(oldfd);
    printf("newfd = %d\n",newfd);   // newfd和oldfd数值不同
    // newfd的数值是所有文件描述符中，最小可用的

    write(oldfd,"hello",5);
    write(newfd,"world",5);

    return 0;
}

