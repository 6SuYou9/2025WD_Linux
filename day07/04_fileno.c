#include <2025Linux.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    // ./04_fileno file
    ARGS_CHECK(argc,2);
    FILE * fp = fopen(argv[1],"r+");
    ERROR_CHECK(fp,NULL,"fopen");

    ssize_t ret = write(3,"hello",5);
    printf("ret = %ld\n",ret);

    fclose(fp);
    return 0;
}

