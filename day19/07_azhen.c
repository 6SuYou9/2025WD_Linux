#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./07_azhen 192.168.196.135 12345
    ARGS_CHECK(argc,3);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;      // ipv4
    addr.sin_port = htons(atoi(argv[2]));   // "12345"--> 小端 12345 --> 大端12345
    addr.sin_addr.s_addr = inet_addr(argv[1]);  // 将IP地址字符串转化为大端机器数
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sockfd,-1,"socket");
    int flag = 1;   // 定义一个int的flag，值为1说明要无视time_wait
    int ret = setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag));
    ERROR_CHECK(ret,-1,"setsockopt");
    ret = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));;
    ERROR_CHECK(ret,-1,"bind");
    ret = listen(sockfd,10);
    ERROR_CHECK(ret,-1,"listen");

    struct sockaddr_in clientaddr;
    socklen_t socklen = sizeof(clientaddr); //规定socklen必须赋初值
    int netfd = accept(sockfd,(struct sockaddr *)&clientaddr,&socklen);
    printf("netfd = %d, client ip = %s, client port = %d\n",
           netfd,inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
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
            write(netfd,buf,strlen(buf));
        }
        if(FD_ISSET(netfd,&rdset)){
            memset(buf,0,sizeof(buf));
            recv(netfd,buf,sizeof(buf),0);
            printf("buf = %s\n",buf);
        }
    }
    return 0;
}

