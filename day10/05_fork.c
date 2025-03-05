#include <2025Linux.h>

int main(int argc,char *argv[])
{
    printf("Hello\n");
    fork();
    printf("World\n");
    return 0;
}

