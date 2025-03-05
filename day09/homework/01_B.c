#include <2025Linux.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    // ./01_B 1.pipe
    ARGS_CHECK(argc,2);
    int pipefdr = open(argv[1],O_RDONLY);
    ERROR_CHECK(pipefdr,-1,"open pipe");
    // 接收文件名
    char filename[1024] = {0}; //不知道文件名有多长，只能申请一个足够大的空间
    int length;
    read(pipefdr,&length,sizeof(length));   // 先读四个字节
    read(pipefdr,filename,length);
    // 根据文件名字新建文件
    char filepath[4096] = {0};
    int ret = mkdir("./test",0777);
    ERROR_CHECK(ret,-1,"mkdir");
    sprintf(filepath,"%s/%s","test",filename);
    int filefdw = open(filepath,O_WRONLY|O_CREAT|O_TRUNC,0666);
    ERROR_CHECK(filefdw,-1,"open file");
    // 获取文件长度
    ssize_t filelength;
    read(pipefdr,&length,sizeof(length));
    read(pipefdr,&filelength,length);
    printf("filelength = %ld\n",filelength);
    // 获取文件的内容
    char buf[4096] = {0};
    read(pipefdr,&length,sizeof(length));
    read(pipefdr,buf,length);
    write(filefdw,buf,length);  // 写入文件
    return 0;
}
