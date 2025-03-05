#include <2025Linux.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    if(fork()){
        wait(NULL);
    }else{
        execl("ls",NULL);
    }
    return 0;
}

