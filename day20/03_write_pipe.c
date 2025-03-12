#include <2025Linux.h>
int main(int argc,char *argv[])
{
    // ./03_write_pipe pipe
    int fd = open(argv[1],O_WRONLY);
    char buf[3] = {0};
    write(fd,"How are you",11);
    while(1){
        sleep(1);
    }
    return 0;
}

