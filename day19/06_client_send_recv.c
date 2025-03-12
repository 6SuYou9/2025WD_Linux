#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./06_client_send_recv 192.168.196.135 12345
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

    sleep(5);
    printf("sleep over!\n");
    close(sockfd);
    send(sockfd,"Hello SuYou",11,0);
    char buf[4096] = {0};
    recv(sockfd,buf,sizeof(buf),0);
    printf("buf = %s\n",buf);
    
    return 0;
}

