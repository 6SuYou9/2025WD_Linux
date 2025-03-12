#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./04_server 192.168.196.135 12345
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
    while(1){   // 保证服务端不退出
        sleep(1);
    }
    return 0;
}

