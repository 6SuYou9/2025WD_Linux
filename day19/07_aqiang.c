#include <2025Linux.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    // ./07_aqiang 192.168.196.135 12345
    ARGS_CHECK(argc,3);
    // 赋值是具体类型
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;      // ipv4
    addr.sin_port = htons(atoi(argv[2]));   // "12345"--> 小端 12345 --> 大端12345
    addr.sin_addr.s_addr = inet_addr(argv[1]);  // 将IP地址字符串转化为大端机器数
    // 创建文件对象 socket
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sockfd,-1,"socket");
    // connect 到服务端，注意客户端不推荐bind，所以不需要bind
    int ret = connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"bind");

    char buf[4096] = {0};
    fd_set rdset;
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(sockfd,&rdset);
        select(sockfd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            memset(buf,0,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));
            write(sockfd,buf,strlen(buf));
        }
        if(FD_ISSET(sockfd,&rdset)){
            memset(buf,0,sizeof(buf));
            recv(sockfd,buf,sizeof(buf),0);
            printf("buf = %s\n",buf);
        }
    }
    return 0;
}

