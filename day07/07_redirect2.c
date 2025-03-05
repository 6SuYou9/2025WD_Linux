#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./07_redirect2 file
    ARGS_CHECK(argc,2);
    int oldfd = open(argv[1],O_RDWR);
    ERROR_CHECK(oldfd,-1,"open");
    printf("You can see me!\n");
    close(STDOUT_FILENO);   // 先关了1
    int newfd = dup(oldfd); // 再dup，newfd就是1
    printf("newfd = %d\n",newfd);
    printf("You can't see me!\n");
    close(newfd);
    close(oldfd);
    return 0;
}

