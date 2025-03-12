#include <2025Linux.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>
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

    int netfd = accept(sockfd,NULL,NULL);
    printf("client1 is connected! netfd1 = %d\n",netfd);

    // 申请和epoll相关的数据结构
    int epfd = epoll_create(1);
    // 设置监听 netfd and stdin
    struct epoll_event event;   // 记录将来fd就绪之后，往就绪队列里放的信息
    event.events = EPOLLIN;     // 说明这是读就绪
    event.data.fd = STDIN_FILENO;   // 将来STDIN就绪之后，把文件描述符填入队列
    // 设置stdin的监听
    epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    // epoll_ctl 中的event是一个传入传出参数，内容可能会被改掉
    event.events = EPOLLIN; // 说明读就绪
    event.data.fd = netfd;  // 将来netfd就绪以后，把netfd放入就绪队列
    // 设置netfd的监听
    epoll_ctl(epfd,EPOLL_CTL_ADD,netfd,&event);
    
    struct epoll_event readyset[FD_SIZE];  // 给将来的就绪集合申请空间
    char buf[BUFSIZE];
    while(1){
        int readynum = epoll_wait(epfd,readyset,FD_SIZE,-1);
        // 运行到这里说明有就绪
        for(int i=0;i<readynum;i++){
            // select和epoll的最大区别
            // select：根据监听的fd数量，执行多次FD_ISSET
            // epoll：根据readynum，执行多次操作
            // if的条件由前面自己设定的放入就绪队列的数据决定
            if(readyset[i].data.fd==STDIN_FILENO){
                memset(buf,0,BUFSIZE);
                read(STDIN_FILENO,buf,BUFSIZE);
                send(netfd,buf,strlen(buf),0);
            }
            else if(readyset[i].data.fd==netfd){
                memset(buf,0,BUFSIZE);
                recv(netfd,buf,BUFSIZE,0);
                printf("buf = %s\n",buf);
            }
        }
    }
    return 0;
}

