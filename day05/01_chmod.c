#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./01_chmod.c 777 file1
    ARGS_CHECK(argc,3);
    // 777 -> 八进制的 777
    mode_t mode;
    sscanf(argv[1],"%o",&mode);// 可以把一个字符串转化为一个整数，%o是八进制
    int ret = chmod(argv[2],mode);
    ERROR_CHECK(ret,-1,"chmod");
    return 0;
}

