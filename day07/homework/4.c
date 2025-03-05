#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./4 file    
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR | O_CREAT | O_TRUNC,0666);	// 1号文件描述符指向打开文件
    ERROR_CHECK(fd,-1,"open");
    printf("\n");
	dup2(fd,STDOUT_FILENO);
    dup2(fd,STDERR_FILENO);		// 让3号文件描述符也指向打开文件
    printf("Hello\n");
    fprintf(stderr,"World\n");;

    return 0;
}
