#include <2025Linux.h>
#include <fcntl.h>
void setNonblock(int fd){
    int flag = fcntl(fd,F_GETFL);//获取当前fd的属性
    flag = flag|O_NONBLOCK; // 在原来的属性的基础上添加非阻塞属性
    fcntl(fd,F_SETFL,flag); // 修改fd的属性
}
int main(int argc,char *argv[])
{
    // ./03_read_pipe pipe
    int fd = open(argv[1],O_RDONLY);
    setNonblock(fd);
    char buf[3] = {0};
    while(1){
        memset(buf,0,sizeof(buf));
        ssize_t sret = read(fd,buf,2);
        printf("sret = %ld, buf = %s\n",sret,buf);
        if(sret==-1){
            break;
        }
        sleep(1);
    }
    return 0;
}

