#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./06_rmdir dir
    ARGS_CHECK(argc,2);
    int ret = rmdir(argv[1]);
    ERROR_CHECK(ret,-1,"rmdir");
    return 0;
}

