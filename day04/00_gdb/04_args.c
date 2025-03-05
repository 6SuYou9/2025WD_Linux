#include <stdio.h>
int main(int argc,char *argv[])
{
    printf("argc = %d\n",argc);
    for(int i = 0;i<argc;++i){
        printf("argc = %s\n",argv[i]);
    }
    return 0;
}

