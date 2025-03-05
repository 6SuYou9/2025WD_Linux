#include <2025Linux.h>

int main(int argc,char *argv[])
{
    printf("You can see me! pid = %d\n",getpid());
    execl("exe","./exe","how","are","you",NULL);
    printf("You can't see me! pid= %d\n",getpid());
    return 0;
}

