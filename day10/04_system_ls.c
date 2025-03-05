#include <2025Linux.h>

int main(int argc,char *argv[])
{
    printf("Before system!\n");
    system("ls -al");
    printf("After system!\n");
    return 0;
}

