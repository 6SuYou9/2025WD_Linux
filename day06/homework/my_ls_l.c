#include <2025Linux.h>

// 将文件模式转换为字符串表示
const char *get_file_type(mode_t mode) {
    if (S_ISREG(mode)) return "-";  // 普通文件
    if (S_ISDIR(mode)) return "d";  // 目录
    if (S_ISCHR(mode)) return "c";  // 字符设备
    if (S_ISBLK(mode)) return "b";  // 块设备
    if (S_ISFIFO(mode)) return "p"; // 管道
    if (S_ISLNK(mode)) return "l";  // 符号链接
    if (S_ISSOCK(mode)) return "s"; // 套接字
    return "?";                     // 未知类型
}

// 将文件权限转换为字符串表示
void get_file_permissions(mode_t mode, char *perms) {
    perms[0] = (mode & S_IRUSR) ? 'r' : '-';
    perms[1] = (mode & S_IWUSR) ? 'w' : '-';
    perms[2] = (mode & S_IXUSR) ? 'x' : '-';
    perms[3] = (mode & S_IRGRP) ? 'r' : '-';
    perms[4] = (mode & S_IWGRP) ? 'w' : '-';
    perms[5] = (mode & S_IXGRP) ? 'x' : '-';
    perms[6] = (mode & S_IROTH) ? 'r' : '-';
    perms[7] = (mode & S_IWOTH) ? 'w' : '-';
    perms[8] = (mode & S_IXOTH) ? 'x' : '-';
    perms[9] = '\0';
}

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

		// 获取文件类型和权限
        char perms[10];
        get_file_permissions(statbuf.st_mode, perms);

        // 获取用户名和组名
        struct passwd *pwd = getpwuid(statbuf.st_uid);
        struct group *grp = getgrgid(statbuf.st_gid);

		// 格式化时间
        char timebuf[80];
        struct tm *tm_info = localtime(&statbuf.st_mtime);
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm_info);
		
        // 打印文件信息
        printf("%s%s %2ld %s %s %8ld %s %s\n",
               get_file_type(statbuf.st_mode), // 文件类型
               perms,                        // 文件权限
               statbuf.st_nlink,              // 硬链接数量
               pwd->pw_name,                  // 用户名
               grp->gr_name,                  // 组名
               statbuf.st_size,               // 文件大小
               timebuf,                       // 修改时间
               direntp->d_name);              // 文件名
    }
    closedir(dirp);
    return 0;
}
