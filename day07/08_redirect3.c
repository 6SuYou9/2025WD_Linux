#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./08_redirect3  file
    ARGS_CHECK(argc,2);
    int oldfd = open(argv[1],O_RDWR); 
    ERROR_CHECK(oldfd,-1,"open");
    printf("1 我过来了！\n");
    int backfd = 10; // backfd用来备份屏幕
    dup2(STDOUT_FILENO,backfd);
    dup2(oldfd,STDOUT_FILENO);  // 让1关联文件
    printf("2 我过去了！在文件哦！\n");
    dup2(backfd,STDOUT_FILENO); // 让1重新指回屏幕
    printf("3 我又回来啦！\n");
    close(backfd);
    close(oldfd);
    return 0;
}

