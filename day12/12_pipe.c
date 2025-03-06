#include <2025Linux.h>

int main(int argc,char *argv[])
{
    int fds[2];
    pipe(fds);
    printf("fds[0] = %d, fds[1] = %d\n",fds[0],fds[1]);
    write(fds[1],"Hello SuYou",11); 
    char buf[4096] = {0};
    read(fds[0],buf,sizeof(buf));
    printf("buf = %s\n",buf);
    return 0;
}

