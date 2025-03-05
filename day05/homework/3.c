#include <2025Linux.h>

// 递归打印目录结构
int print_tree(const char *dir_path, int level) {
    DIR *dirp = opendir(dir_path);
    ERROR_CHECK(dirp,NULL,"opendir");

    struct dirent *direntp;
    while ((direntp = readdir(dirp)) != NULL) {
        // 忽略当前目录和父目录
        if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0) {
            continue;
        }

        // 打印缩进
        for (int i = 0; i < level; i++) {
            printf("│   ");
        }

        // 打印当前目录项
        printf("├── %s\n", direntp->d_name);

        // 构建子目录的完整路径
        char subdir_path[1024];
        snprintf(subdir_path, sizeof(subdir_path), "%s/%s", dir_path, direntp->d_name);

        // 检查是否是目录
        struct stat statbuf;
        if (stat(subdir_path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
            // 递归打印子目录
            print_tree(subdir_path, level + 1);
        }
    }

    closedir(dirp);
}

int main(int argc, char *argv[]) {
    ARGS_CHECK(argc, 2);

    printf("%s\n", argv[1]); // 打印根目录
    print_tree(argv[1], 0);  // 从根目录开始递归打印

    return 0;
}
