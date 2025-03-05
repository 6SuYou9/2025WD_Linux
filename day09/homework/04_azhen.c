#include <2025Linux.h>
#include <time.h>

int main(int argc,char *argv[])
{
    // ./04_azhen 1.pipe 2.pipe
    ARGS_CHECK(argc,3);
    int fdw = open(argv[1],O_WRONLY);
    int fdr = open(argv[2],O_RDONLY);
    char buf[4096] = {0};
    ssize_t ret;
    time_t lastactive=time(NULL),now;
    printf("azhen is connected!\n");
    // 1 创建监听集合
    fd_set rdset;   // rdset是监听集合
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(fdr,&rdset);
        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        int sret = select(fdr+1,&rdset,NULL,NULL,&timeout);    // 有资源就绪or超时都会令select就绪
		now = time(NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset)){  // 用户输入了一些消息
            memset(buf,0,sizeof(buf));
            ret = read(STDIN_FILENO,buf,sizeof(buf));
			if(ret == 0){   // 主动退出
				write(fdw,"You are a good people!",22);
				break;
			}
            write(fdw,buf,strlen(buf));
        }
        if(FD_ISSET(fdr,&rdset)){   // 对方发送了一些消息
            lastactive = time(NULL);
            memset(buf,0,sizeof(buf));
            ret = read(fdr,buf,sizeof(buf));
			if(ret == 0){
				printf("hehe!\n");
				break;
			}
            printf("Received:%s\n",buf);
             
        }
		if(now - lastactive>=10)
		{
			printf("你是舔狗，别等了，给你挂了!\n");
			break;
		}
    }
        close(fdw);
        close(fdr);
    return 0;
}
