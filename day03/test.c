#include <stdio.h>  // 在系统路径下搜索 /usr/include 和 /usr/local/include
#include "test.h"   // 在.c文件的当前目录下搜索
#define X 1+2
#define TEST(a,b){a=b;}
int main()
{
    int x = X;
    int y = 0;
    TEST(x,y);
    printf("Hello world\n");
    printf("Hello SuYou!");
    return 0;
}
