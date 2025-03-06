#include <2025Linux.h>

int main(int argc,char *argv[])
{
    FILE * fp = popen("./child_write","r");
    char buf[4096] = {0};
    fread(buf,1,sizeof(buf),fp);
    printf("buf = %s\n",buf);
    pclose(fp);
    return 0;
}

