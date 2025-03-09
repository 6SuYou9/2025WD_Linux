#include <2025Linux.h>

int main(int argc,char *argv[])
{
    if(fork()){
        wait(NULL);
		printf("child is closed!\n");
    }else{
        execl("ls",",.ls",NULL);
    }
    return 0;
}

