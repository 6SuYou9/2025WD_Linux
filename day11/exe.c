#include <2025Linux.h>

int main(int argc,char *argv[])
{
    printf("pid = %d, argc = %d\n",getpid(),argc);
    for(int i = 0;i<argc;i++){
        printf("argv[%d] = %s\n",i,argv[i]);
    }
    return 0;
}

