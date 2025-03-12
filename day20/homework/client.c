#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./client 0.0.0.0 12345
    ARGS_CHECK(argc,3);
    // 1.初始化变量
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;  // 代表piv4
    // 把端口号字符串转为数字再转化为大端存储
    addr.sin_port = htons(atoi(argv[2]));
    addr.sin_addr.s_addr = inet_addr(argv[1]); 
     
    // 2.创建socket文件对象
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sockfd,-1,"socket");
    // 3.客户端直接connect，服务端才需要bind
    int ret = connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    ERROR_CHECK(ret,-1,"connect");
    // 4.连接成功
    fd_set rdset;
    char buf[4096] = {0};
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(sockfd,&rdset);
        select(sockfd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            memset(buf,0,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));
            send(sockfd,buf,sizeof(buf),0);
        }
        if(FD_ISSET(sockfd,&rdset)){
            memset(buf,0,sizeof(buf));
            ssize_t sret = recv(sockfd,buf,sizeof(buf),0);
            if(sret==0){
                printf("server is closed!\n");
                break;
            }
            printf("buf = %s\n",buf);
        }
    }
    close(sockfd);
    return 0;
}
