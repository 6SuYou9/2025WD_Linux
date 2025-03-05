#include <2025Linux.h>

int main(int argc,char *argv[])
{
    if(fork()){
        return 0;
    }else{
        while(1){
            sleep(1);
        }
    }
    return 0;
}

