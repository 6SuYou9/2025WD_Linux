#include <2025Linux.h>
#define IP "0.0.0.0"    // argv[1]
#define PORT "12345"      // argv[2]
#define BUFSIZE 4096
int main(int argc,char *argv[])
{
    // ./4_server 0.0.0.0 12345 测试先用宏了
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

    // 做两次accept
    int netfd1,netfd2;
    netfd1 = accept(sockfd,NULL,NULL);
    printf("client1 is connected! netfd1 = %d\n",netfd1);
    netfd2 = accept(sockfd,NULL,NULL);
    printf("client2 is connected! netfd2 = %d\n",netfd2);
    
    // 准备select 监听netfd1和netfd2，每次监听集合都是一样的，可以不要监听和就绪分离
    fd_set rdset;
    char buf[BUFSIZE];
    while(1){
        FD_ZERO(&rdset);
        FD_SET(netfd1,&rdset);
        FD_SET(netfd2,&rdset);
        select(netfd2+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(netfd1,&rdset)){
            memset(buf,0,BUFSIZE);
            recv(netfd1,buf,BUFSIZE,0);
            send(netfd2,buf,strlen(buf),0);
        }
        if(FD_ISSET(netfd2,&rdset)){
            memset(buf,0,BUFSIZE);
            recv(netfd2,buf,BUFSIZE,0);
            send(netfd1,buf,strlen(buf),0);
        }
    }
    return 0;
}

