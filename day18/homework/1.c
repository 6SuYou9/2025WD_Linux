#include <stdio.h>

// 函数：检测字节序
int check_endianess() {
    unsigned int x = 1; // 整数1在内存中表示为：00 00 00 01（小端）或 01 00 00 00（大端）
    return !((char *)&x)[0]; // 如果是小端模式，最低地址存储的是最低位字节，值为1
}

int main() {
    if (check_endianess()) {
        printf("This machine is Big-Endian.\n");
    } else {
        printf("This machine is Little-Endian.\n");
    }
    return 0;
}
