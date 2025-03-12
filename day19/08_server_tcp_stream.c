#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./06_server_send_recv 192.168.196.135 12345
    ARGS_CHECK(argc,3);
    // 赋值是具体类型
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;      // ipv4
    addr.sin_port = htons(atoi(argv[2]));   // "12345"--> 小端 12345 --> 大端12345
    addr.sin_addr.s_addr = inet_addr(argv[1]);  // 将IP地址字符串转化为大端机器数
    // 创建文件对象 socket
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(sockfd,-1,"socket");
    // 关联socket和网络地址
    int ret = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));;
    //  对网络地址addr取地址 --> 强转为公共类型struct sockaddr的指针
    ERROR_CHECK(ret,-1,"bind");
    ret = listen(sockfd,10);
    ERROR_CHECK(ret,-1,"listen");

    struct sockaddr_in clientaddr;
    socklen_t socklen = sizeof(clientaddr); //规定socklen必须赋初值
    int netfd = accept(sockfd,(struct sockaddr *)&clientaddr,&socklen);
    // 一旦accept返回，说明连接取出来了，通信的socket的fd是netfd
    printf("netfd = %d, client ip = %s, client port = %d\n",
           netfd,inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
    char buf[4096] = {0};
    ssize_t sret = recv(netfd,buf,sizeof(buf),0);
    printf("sret = %ld, buf = %s\n",sret,buf);
    return 0;
}

