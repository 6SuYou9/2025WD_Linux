#include "tcpInit.h"
#include <2025Linux.h>
int tcpInit(const char *ip,const char *port){
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    // 下面三行可以让服务器断开连接后不管2MSL
    int flag = 1;
    int ret = setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag));
    ERROR_CHECK(ret,-1,"setsockopt");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = inet_addr(ip);
    
    ret = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");
    listen(sockfd,50);
    
    return sockfd;
}
