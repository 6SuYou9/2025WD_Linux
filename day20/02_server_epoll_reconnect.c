#include <2025Linux.h>
#define IP "0.0.0.0"    // argv[1]
#define PORT "12345"      // argv[2]
#define BUFSIZE 4096
#define FD_SIZE 1024
int main(int argc,char *argv[])
{
    // ./01_server_epoll 0.0.0.0 12345 测试先用宏了
    ARGS_CHECK(argc,1);
    // 初始化变量
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(PORT));
    addr.sin_addr.s_addr = inet_addr(IP);
    // 创建socket文件对象
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sockfd,-1,"socket");
    int flag = 1;
    int ret = setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag));
    ERROR_CHECK(ret,-1,"setsockopt");
    // 服务端需要bind
    ret = bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");
    // 服务端需要listen
    ret = listen(sockfd,10);
    ERROR_CHECK(ret,-1,"listen");

    // 申请和epoll相关的数据结构
    int epfd = epoll_create(1);
    // 设置监听
    struct epoll_event event;   // 记录将来fd就绪之后，往就绪队列里放的信息
    event.events = EPOLLIN;     // 说明sockfd是读就绪
    event.data.fd = sockfd;   // 将来sockfd就绪之后，把文件描述符填入队列
    // 设置sockfd的监听
    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&event);
    
    struct epoll_event readyset[FD_SIZE];  // 给将来的就绪集合申请空间
    char buf[BUFSIZE];
    int netfd = -1; // -1 说明阿强断开连接了
    while(1){
        int readynum = epoll_wait(epfd,readyset,FD_SIZE,-1);
        // 运行到这里说明有就绪
        for(int i=0;i<readynum;i++){
            if(readyset[i].data.fd==sockfd){
                // 有客户端连接，可以调用accept
                netfd = accept(sockfd,NULL,NULL);
                event.events = EPOLLIN;
                event.data.fd =STDIN_FILENO;
                epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
                event.events = EPOLLIN;
                event.data.fd =netfd;
                epoll_ctl(epfd,EPOLL_CTL_ADD,netfd,&event);
                // 移除sockfd的监听
                epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,NULL);  // 移除监听第四个参数可以是NULL
            }
            else if(readyset[i].data.fd==STDIN_FILENO){
                // 阿珍说话了
                memset(buf,0,BUFSIZE);
                read(STDIN_FILENO,buf,BUFSIZE);
                send(netfd,buf,strlen(buf),0);
            }
            else if(readyset[i].data.fd==netfd){
                // 阿强说话了或者阿强断开了
                memset(buf,0,BUFSIZE);
                ssize_t sret = recv(netfd, buf,BUFSIZE,0);
                if(sret==0){
                    // 阿强断开了
                    epoll_ctl(epfd,EPOLL_CTL_DEL,netfd,NULL);
                    epoll_ctl(epfd,EPOLL_CTL_DEL,STDIN_FILENO,NULL);
                    event.events = EPOLLIN;
                    event.data.fd = sockfd;
                    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&event);
                    close(netfd);
                    netfd = -1;
                    printf("我会好好的！\n");
                    continue;
                }
                // 阿强发消息了
                printf("buf = %s\n",buf);
            }
        }
    }
    return 0;
}

