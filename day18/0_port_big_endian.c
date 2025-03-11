#include <2025Linux.h>

int main(int argc,char *argv[])
{
    unsigned short port = 0x1234;   // 小端的
    unsigned short big_endian_port = htons(port);   // 从小端变成大端
    printf("%d\n",big_endian_port);     // 没有意义，用小端的方式解释一个大端的数据
    printf("%x\n",big_endian_port);     // 看看它的16进制
    return 0;
}

