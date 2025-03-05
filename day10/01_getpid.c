#include <2025Linux.h>

int main(int argc,char *argv[])
{
    printf("pid = %d,ppid = %d\n",getpid(),getppid());    
    return 0;
}

