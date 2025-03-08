#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./8_mykill pid
    ARGS_CHECK(argc,2);
    kill(atoi(argv[1]),SIGKILL);        // atoi是将一个字符串或者字符数组转化对于的整数
    return 0;
}

