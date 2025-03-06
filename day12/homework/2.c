#include <2025Linux.h>
#define FD_MAX 1024

int main(int argc,char *argv[])
{
    if(fork()){
        exit(0);
    }else{
        for(int i=0;i<FD_MAX;i++){
            close(i);
        }
        chdir("/");
        umask(0);   // umask(0) 取消所有权限限制，使新文件/目录的权限等于初始值
    }
    while(1) sleep(1);
    return 0;
}

