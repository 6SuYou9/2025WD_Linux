#include <2025Linux.h>
#define MAXSIZE 1024

int main(int argc,char *argv[])
{
    // ./2 file1 file2
    ARGS_CHECK(argc,3); // 检验参数
    // 打开两个文件
    int fd1 = open(argv[1],O_RDONLY);
    ERROR_CHECK(fd1,-1,"open fd1");
    int fd2 = open(argv[2],O_RDONLY);
    ERROR_CHECK(fd2,-1,"open fd2");

    // 读取两个文件
    char buf1[MAXSIZE] = {0};
    char buf2[MAXSIZE] = {0};
    int flag = 1;
    while(1){
        memset(buf1,0,MAXSIZE);
        memset(buf2,0,MAXSIZE);
        ssize_t ret1 = read(fd1,buf1,MAXSIZE);
        ERROR_CHECK(ret1,-1,"read 1");
        ssize_t ret2 = read(fd2,buf2,MAXSIZE);
        ERROR_CHECK(ret2,-1,"read 2");
        int ret = memcmp(buf1,buf2,MAXSIZE);
        if(ret1!=ret2 || ret!=0){
            flag = 0;
            break;
        }
        else if(ret1==0 || ret2 == 0) break;
    }
    if (flag == 1) {
        printf("Files are identical.\n");
    } else {
        printf("Files are different.\n");
    }
    return 0;
}

