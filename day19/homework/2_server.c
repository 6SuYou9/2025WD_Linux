#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./2_server 0.0.0.0 12345
    ARGS_CHECK(argc,3);
    // 1.初始化变量
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    // 2.创建socket文件对象
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sockfd,-1,"socket");
    // 3.服务端需要bind
    int ret = bind(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");
    // 4.服务端需要listen
    ret = listen(sockfd,10);
    ERROR_CHECK(ret,-1,"listen");
    // 5.服务端accept
    struct sockaddr_in clientaddr;
    socklen_t clientaddrlen = sizeof(clientaddr);
    int netfd = accept(sockfd,(struct sockaddr *)&clientaddr,&clientaddrlen);
    ERROR_CHECK(netfd,-1,"accept");
    printf("netfd = %d, ip = %s, port = %d\n",
           netfd,inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
    // 6.连接成功后进行通信
    char buf[4096] = {0};
    fd_set rdset;
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(netfd,&rdset);
        select(netfd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            memset(buf,0,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));
            send(netfd,buf,sizeof(buf),0);
        }
        if(FD_ISSET(netfd,&rdset)){
            memset(buf,0,sizeof(buf));
            recv(netfd,buf,sizeof(buf),0);
            printf("buf = %s\n",buf);
        }
    }
    return 0;
}

