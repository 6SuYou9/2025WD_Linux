#include <2025Linux.h>

int main(int argc,char *argv[])
{
    FILE * fp = popen("./child_read","w");
    // fp就是管道的写端
    fwrite("5 6",1,3,fp);
    pclose(fp);
    return 0;
}

