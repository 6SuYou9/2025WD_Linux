#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./07_myls dir1
    ARGS_CHECK(argc,2);
    DIR *dirp = opendir(argv[1]);   // 创建目录流
    ERROR_CHECK(dirp,NULL,"opendir");   // 检查目录流是否创建成功
    struct dirent * direntp;    // readdir会为dirent申请内存(在数据段上)
    int i = 0;
    while((direntp = readdir(dirp)) != NULL){  // 使用while+readdir依次取出目录项
        printf("dirent%d name = %s\n",++i,direntp->d_name);  // 目录项中有文件名的信息
    }

    closedir(dirp); // 关闭目录流
    return 0;
}

