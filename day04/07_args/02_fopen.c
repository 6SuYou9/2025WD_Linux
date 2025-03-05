#include<2025Linux.h>
#include <stdio.h>
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    FILE *fp;
    fp = fopen(argv[1],"a");
    ERROR_CHECK(fp,NULL,"fopen");   
    fseek(fp,0,SEEK_SET);   // 将ptr放在文件的开始位置
    fwrite("SuYou",1,5,fp);
    fclose(fp);
    return 0;
}
