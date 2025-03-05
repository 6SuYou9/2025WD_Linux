#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./5 file1 file2
    ARGS_CHECK(argc,3);
	// 打开两个文件
    close(STDOUT_FILENO);
    int fd1 = open(argv[1],O_RDWR | O_CREAT | O_TRUNC,0666);	// 使1号文件描述符指向第一个文件
    ERROR_CHECK(fd1,-1,"open fd1");
	int fd2 = open(argv[2],O_RDWR | O_CREAT | O_TRUNC,0666);
	ERROR_CHECK(fd1,-1,"open fd2");
	
    close(STDERR_FILENO);
    dup2(fd2,STDERR_FILENO);	// 使3号文件描述符指向第二个文件
    printf("Hello\n");
    fprintf(stderr,"World\n");;

    return 0;
}

