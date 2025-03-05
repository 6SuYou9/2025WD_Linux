#include <2025Linux.h>

int main(int argc,char *argv[])
{
    if(fork()){
        while(1){
            sleep(1);
        }
    }else{
        return 0;
    }
    return 0;
}

