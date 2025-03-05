#include <2025Linux.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    if(fork()){
        int wstatus;
        wait(&wstatus);
        if(WIFEXITED(wstatus)){
            printf("wstatus = %d\n",WEXITSTATUS(wstatus));
        }
    }else{
        exit(-1);
    }   
    return 0;
}

