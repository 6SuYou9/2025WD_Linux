#include <2025Linux.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    // ./03_toupper file
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");

    char ch;
    while(1){
        ssize_t ret = read(fd,&ch,1);
        if(ret == 0) break;
        if(ch>='a'&&ch<='z'){
            ch -=32;
            lseek(fd,-1,SEEK_CUR);
            write(fd,&ch,1);
        }
    }
    close(fd);
    return 0;
}

