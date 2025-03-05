#include <2025Linux.h>

int main(int argc,char *argv[])
{
    if(fork()){
        exit(0);
    }else{
        printf("Before setsid, sid = %d\n",getsid(0));
        setsid();
        printf("After setsid, sid = %d\n",getsid(0));

    } 
    return 0;
}

