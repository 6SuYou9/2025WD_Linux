#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./4 file1
    ARGS_CHECK(argc,2);
    struct stat statbuf;    // main函数申请在栈上的数据
    int ret = stat(argv[1],&statbuf); //取地址statbuf传入stat函数
    ERROR_CHECK(ret,-1,"stat");
    // 当stat调用完成之后，statbuf存储了一些信息
    printf("mode = %o\n",statbuf.st_mode);  //文件的权限和类型
    return 0;
}

