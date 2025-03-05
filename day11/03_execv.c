#include <2025Linux.h>

int main()
{
    printf("You can see me! pid = %d\n",getpid());
    char *const argv[] = {"how","are","you",NULL};
    execv("exe",argv);
    printf("You can't see me! pid= %d\n",getpid());
    return 0;
}

