#include <2025Linux.h>

int main(int argc,char *argv[])
{
	// ./3 file
	ARGS_CHECK(argc,2);
    char buf[1000*1000];
    memset(buf,'1',sizeof(buf));	// 注意buf不是字符串，是一个字符数组
    int fd = open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(fd,-1,"open");
    ssize_t ret = write(fd,buf,sizeof(buf));
    ERROR_CHECK(ret,-1,"write");
    return 0;
}
