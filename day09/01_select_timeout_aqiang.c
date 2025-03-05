#include <2025Linux.h>
#include <time.h>

int main(int argc,char *argv[])
{
    // ./01_select_timeout_aqiang 1.pipe 2.pipe
    ARGS_CHECK(argc,3);
    int fdr = open(argv[1],O_RDONLY);
    int fdw = open(argv[2],O_WRONLY);
    char buf[4096] = {0};
	ssize_t ret;
    printf("aqiang is connected!\n");
    // 1 创建监听集合
    fd_set rdset;   // rdset是监听集合
    while(1){
        // 2 初始化监听集合
        FD_ZERO(&rdset);
        // 3 将需要关注的资源加入监听集合
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(fdr,&rdset);
        struct timeval timeout;
        timeout.tv_sec = 3;
        timeout.tv_usec = 0;
        // 4 内核轮询 用户等待
        // 最大的fd是fdr，监听的读操作在rdset，没有写操作和异常操作，超时时间是永久
        int sret = select(fdr+1,&rdset,NULL,NULL,&timeout);    // 有资源就绪or超时都会令select就绪
        if(sret==0)
        {
            printf("select is returned!\n");
            time_t now = time(NULL);
            printf("now = %s\n",ctime(&now));

        }
        // 5 select 返回了，rdset是就绪集合，rdset中有一个fd就绪了
        if(FD_ISSET(STDIN_FILENO,&rdset)){  // 用户输入了一些消息
            memset(buf,0,sizeof(buf));
            ret = read(STDIN_FILENO,buf,sizeof(buf));
			if(ret == 0){	// 主动退出
	            write(fdw,"You are a good people!",22);
				break;
			}
            write(fdw,buf,strlen(buf));
        }
        if(FD_ISSET(fdr,&rdset)){   // 对方发送了一些消息
            memset(buf,0,sizeof(buf));
            ret = read(fdr,buf,sizeof(buf));
			if(ret == 0){
				printf("hehe!\n");
				break;
			}
            printf("Received:%s\n",buf);
             
        }
    }
	close(fdw);
	close(fdr);
    return 0;
}
