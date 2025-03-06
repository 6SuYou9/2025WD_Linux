#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // 子进程做读操作
    int lhs,rhs;
    scanf("%d%d",&lhs,&rhs);
    printf("lhs + rhs = %d\n",lhs+rhs);
    return 0;
}

