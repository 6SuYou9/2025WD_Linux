#include <2025Linux.h>

int func(){
    _exit(234);
}

int main(int argc,char *argv[])
{
    printf("Hello");
    func();
    printf("Can you see me?\n");
    return 0;
}

