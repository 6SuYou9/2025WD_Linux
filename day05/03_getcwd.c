#include <2025Linux.h>

int main()
{
    // ./03_getcwd.c_getcwd
    char *p = getcwd(NULL,0);    //由被调函数自动申请长度
    ERROR_CHECK(p,NULL,"getcwd"); 
    printf("p = %s\n",p);
    return 0;
}

