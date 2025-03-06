#include <2025Linux.h>

int main(int argc,char *argv[])
{
    int fds1[2];
    int fds2[2];
    pipe(fds1);
    pipe(fds2);
    printf("pipe is opened.\n");
    if(fork()){
        close(fds1[0]);
        close(fds2[1]);
       char buf[4096] = {0};
       int cnt = 1;
        //1. 验证是否读阻塞
        //printf("sleep start.\n");
        //sleep(3);
        //printf("sleep over.\n");
        
        // 2.验证是否写阻塞
        printf("write start.\n");
        //2.1
        //write(fds1[1],"Hello SuYou",11);
        //2.2
        //while(1){
            //write(fds1[1],buf,sizeof(buf));
            //printf("write one,cnt = %d\n",cnt++);
        //}
        //printf("write over.\n");
        // 3.验证读端先关闭，写端继续写
        //printf("3 close fds2[0]\n");
        //close(fds2[0]);
        //printf("close fds2[0] over.\n");
        //sleep(100);
        // 4.验证写端先关闭，读端继续读
        printf("4 close fds1[1]\n");
        close(fds1[1]);
        printf("close fds1[1] over.\n");
        sleep(100);
    }else{
        close(fds1[1]);
        close(fds2[0]);
        char buf[4096] = {0};
        // 验证是否读阻塞
        //printf("read start\n");
        //read(fds1[0],buf,sizeof(buf));
        //printf("read over\n");
        // 2,验证是否写阻塞
        //printf("sleep start.\n");
        //sleep(3);
        //printf("sleep over.\n");
        // 3.验证读端先关闭，写端继续写
        //sleep(2);
        //printf("write start\n");
        //write(fds2[1],buf,sizeof(buf));
        //printf("write over\n");
        // 4.验证写端先关闭，读端继续读
        sleep(2);
        printf("read start\n");
        read(fds1[0],buf,sizeof(buf));
        printf("read over\n");
    }


    return 0;
}

