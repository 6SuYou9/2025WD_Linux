#include <2025Linux.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    // 创建dir1
    int ret = mkdir("dir1",0777);
    ERROR_CHECK(ret,-1,"mkdir dir1");
    ret = chdir("dir1");
    ERROR_CHECK(ret,-1,"chdir dir1");

    // 创建dir1/dir2
    ret = mkdir("dir2",0777);
    ERROR_CHECK(ret,-1,"mkdir dir2");
    ret = chdir("dir2");
    ERROR_CHECK(ret,-1,"chdir dir2");
    
    // 创建dir1/dir2/dir3
    ret = mkdir("dir3",0777);
    ERROR_CHECK(ret,-1,"mkdir dir3");
    return 0;
}

