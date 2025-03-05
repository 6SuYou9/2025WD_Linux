#include <2025Linux.h>

int main()
{
    // ./02_getcwd
    char buf[24] = {0};   // 在日常代码中，buf越大越好
    char *p = getcwd(buf,sizeof(buf));
    ERROR_CHECK(p,NULL,"getcwd"); 
    printf("p = %s,buf = %s\n",p,buf);
    return 0;
}

