#include <2025Linux.h>

int main(int argc,char *argv[])
{
    if(fork()){
        while(1){
            sleep(1);
        }
    }else{
        setpgid(0,0);   // 让子进程脱离原来进程组
        while(1){
            sleep(1);
        }
    }
    return 0;
}

