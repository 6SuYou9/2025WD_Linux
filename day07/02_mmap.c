#include <2025Linux.h>
#include <sys/mman.h>

int main(int argc,char *argv[])
{
    // ./02_mmap file    
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);      // 使用O_RDWR
    ERROR_CHECK(fd,-1,"open");
    int ret = ftruncate(fd,5);
    ERROR_CHECK(ret,-1,"ftruncate");    // 防止出现意外，强制修改文件大小为5
    char *p = (char *)mmap(NULL,5,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p,MAP_FAILED,"mmap");
    // 在内存中申请一片空间，这片空间和磁盘文件建立了映射
    // 可以通过访问内存的方式来访问磁盘内容  (*运算符 []运算符)  
    for(int i = 0;i<5;i++){
        printf("%c",p[i]);
    }
    printf("\n");
    p[0] = 'H';
    close(fd);
    munmap(p,5);
    return 0;
}

