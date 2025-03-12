#include <2025Linux.h>
#include <arpa/inet.h>

int main(int argc,char *argv[])
{
    char ip[] = "192.168.124.13"; 
    struct in_addr ipaddr;      // ipaddr是IP地址的机器数
    //inet_aton(ip,&ipaddr);      // 点分十进制转为了大端的机器数
    ipaddr.s_addr = inet_addr(ip);
    printf("ip = %08x\n",ipaddr.s_addr);
    char *ip2 = inet_ntoa(ipaddr);
    printf("%x 转化为的IP地址为 %s\n",ipaddr.s_addr,ip2);
    return 0;
}

