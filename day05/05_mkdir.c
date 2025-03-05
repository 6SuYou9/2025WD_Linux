#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./05_mkdir dir1
    ARGS_CHECK(argc,2);
    int ret = mkdir(argv[1],0777);  
    // 0777是八进制，直接写777，识别不了是八进制
    ERROR_CHECK(ret,-1,"mkdir");
    return 0;
}

