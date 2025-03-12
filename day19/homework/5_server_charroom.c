#include <2025Linux.h>
#define IP "0.0.0.0"    // argv[1]
#define PORT "12345"      // argv[2]
#define BUFSIZE 4096
// 设计一个数据结构数组，管理所有客户端的信息
typedef struct ConnInfo_s{
    int netfd;
    int isConnected;    // 0 未连接 1 已连接
} ConnInfo_t;
int main(int argc,char *argv[])
{
    // ./5_server_charroom 0.0.0.0 12345 测试先用宏了
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

    // 监听和就绪集合分离
    fd_set monitorset;
    fd_set readyset;
    FD_ZERO(&monitorset);
    FD_SET(sockfd,&monitorset); // 最开始的时候只监听sockfd
    // 管理所有客户端信息的数据结构
    ConnInfo_t client[1024];
    for(int i=0;i<1024;i++){    // 初始化
        client[i].isConnected = 0;
    }
    int curidx = 0;     // 下一个客户端在client中的下标
    char buf[BUFSIZE];
    while(1){
        memcpy(&readyset,&monitorset,sizeof(fd_set));
        select(1024,&readyset,NULL,NULL,NULL);  // select不会修改monitorset了
        if(FD_ISSET(sockfd,&readyset)){   // 有新的客户端接入
            // 向client数组中新加一个成员
            client[curidx].netfd = accept(sockfd,NULL,NULL);   // accept之后sockfd依然需要监听
            client[curidx].isConnected = 1;
            printf("new client is isConnected!  id = %d, netfd = %d\n",curidx,client[curidx].netfd);
            // 把新客户端的netfd加入监听
            FD_SET(client[curidx].netfd,&monitorset);
            curidx++;   // 下标自增
        }
        // 某个客户端就绪了，来消息了
        for(int i=0;i<curidx;i++){  //0~curidx-1是所有已经连接的客户端
            if(client[i].isConnected==1 && FD_ISSET(client[i].netfd,&readyset)){    // 逻辑与的短路性
                // 读消息
                memset(buf,0,BUFSIZE);
                ssize_t sret = recv(client[i].netfd,buf,BUFSIZE,0);
                if(sret==0){    // 某个客户端断开了
                    FD_CLR(client[i].netfd,&monitorset);    // 移除对其的监听
                    close(client[i].netfd); 
                    client[i].isConnected = 0;  // 修改client[i]设为未连接
                    continue;
                }
                // 确实有消息
                printf("get message, id = %d, netfd = %d\n",i,client[i].netfd);
                for(int j=0;j<curidx;j++){
                    if(client[j].isConnected==1 && j!=i){   // 遍历存活的其他client
                        send(client[j].netfd,buf,strlen(buf),0);
                    }
                }
            }
        }
    }
    return 0;
}

