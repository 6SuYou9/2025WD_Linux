#include <2025Linux.h>
#include <dirent.h>

int main(int argc,char *argv[])
{
    // ./5my_ls_al dir1
    ARGS_CHECK(argc,2);
    DIR * dirp = opendir(argv[1]);
    ERROR_CHECK(dirp,NULL,"opendir");
    struct dirent * direntp;
    chdir(argv[1]); // 切换当前工作目录到指定路径
    while((direntp = readdir(dirp)) != NULL){
        struct stat statbuf;
        int ret = stat(direntp->d_name,&statbuf);   // 切换目录之后文件名就是文件路径
        ERROR_CHECK(ret,-1,"stat");
        printf("%8o %2ld %s %s %8ld %s %s",
               statbuf.st_mode,     // 文件的类型和权限
               statbuf.st_nlink,    // 文件的硬链接数量
               getpwuid(statbuf.st_uid)->pw_name,   // 根据uid得到用户名
               getgrgid(statbuf.st_gid)->gr_name,   // 根据gid得到组名
               statbuf.st_size,     // 文件的大小
               direntp->d_name,     // 文件的名字
               ctime(&statbuf.st_mtime) // 上次修改时间，是一个时间戳用ctime转化
               );
    }
    closedir(dirp);
    return 0;
}

