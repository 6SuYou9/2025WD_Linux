#include <2025Linux.h>
#include <stdio.h>
#include <sys/select.h>

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
    // 6.因为要实现断线重连，所以要用select等待sockfd有连接再accept
    char buf[4096] = {0};
    fd_set monitorset;
    FD_ZERO(&monitorset);
    FD_SET(sockfd,&monitorset);
    fd_set rdset;
    int netfd = -1; // 代表客户端走了
    // 连接成功后进行通信
    while(1){
        memcpy(&rdset,&monitorset,sizeof(fd_set));// 因为不想让select改变监听集合
        select(1024,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(sockfd,&rdset)){    // 说明可以accept了
            // 服务端accept
            struct sockaddr_in clientaddr;
            socklen_t clientaddrlen = sizeof(clientaddr);
            netfd = accept(sockfd,(struct sockaddr *)&clientaddr,&clientaddrlen);
            ERROR_CHECK(netfd,-1,"accept");
            printf("netfd = %d, ip = %s, port = %d\n",
                   netfd,inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
            // accept之后更新监听集合为stdin和netfd
            FD_CLR(sockfd,&monitorset);
            FD_SET(STDIN_FILENO,&monitorset);
            FD_SET(netfd,&monitorset);
        }
        if(netfd!=-1 && FD_ISSET(STDIN_FILENO,&rdset)){  //客户端存活&&有消息要发送给客户端
            memset(buf,0,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));
            send(netfd,buf,sizeof(buf),0);
        }
        if(netfd!=-1 && FD_ISSET(netfd,&rdset)){    // 客户端存活&&客户端有消息发给服务端
            memset(buf,0,sizeof(buf));
            ssize_t sret = recv(netfd,buf,sizeof(buf),0);
            if(sret==0){    // 客户端断开连接了
                close(netfd);
                netfd = -1;
                printf("客户端断开连接了！\n");
                // 更新监听集合
                FD_ZERO(&monitorset);
                FD_SET(sockfd,&monitorset);
                continue;
            }
            printf("buf = %s\n",buf);
        }
    }

    return 0;
}

