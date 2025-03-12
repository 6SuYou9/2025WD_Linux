#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./09_azhen_reconnect 192.168.196.135 12345
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

    // 因为每次select时，监听集合可能不一样，所以需要把监听和就绪集合分离
    fd_set monitiorset;     // 监听集合
    fd_set readyset;    // 就绪集合
    FD_ZERO(&monitiorset);
    FD_SET(sockfd,&monitiorset);
    char buf[4096] = {0};
    int netfd = -1; // -1 说明阿强死了
    fd_set rdset;
    while(1){
        memcpy(&readyset,&monitiorset,sizeof(fd_set));  // 用monitorset覆盖readyset
        select(1024,&readyset,NULL,NULL,NULL);   // 为什么不写monitorset--->我们希望monitorset不会被select改变
        if(FD_ISSET(sockfd,&readyset)){ // 阿强连上了
             netfd = accept(sockfd,NULL,NULL);
             printf("aqiang is connected!\n");
             FD_CLR(sockfd,&monitiorset);
             FD_SET(STDIN_FILENO,&monitiorset);
             FD_SET(netfd,&monitiorset);
        }
        if(netfd!=-1 && FD_ISSET(STDIN_FILENO,&readyset)){  //  阿强活着 && 阿珍要给阿强发消息
            memset(buf,0,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));
            write(netfd,buf,strlen(buf));
        }
        if(netfd!=-1 && FD_ISSET(netfd,&readyset)){ // 阿强活着 && 阿强给阿珍发消息了
            memset(buf,0,sizeof(buf));
            ssize_t sret = recv(netfd,buf,sizeof(buf),0);
            if(sret==0){
                FD_CLR(STDIN_FILENO,&monitiorset);
                FD_CLR(netfd,&monitiorset);
                FD_SET(sockfd,&monitiorset);
                close(netfd);
                netfd =-1 ;
                printf("阿强走了，我会好好等----\n");
                continue;
            }
            printf("buf = %s\n",buf);
        }
    }
    return 0;
}

