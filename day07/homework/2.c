#include <2025Linux.h>

int main(int argc,char *argv[])
{
    // ./2 file
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");

    struct stat statbuf;
    int ret = stat(argv[1],&statbuf);
    ERROR_CHECK(ret,-1,"stat");
    int size = statbuf.st_size;

    char *p = (char *)mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p,MAP_FAILED,"mmap");
    
	char ch;    // 依次读取转大写
	while(1){
		ssize_t ret = read(fd,&ch,1);
		if(ret == 0) break;
		if(ch>='a'&&ch<='z'){
			ch -=32;
			lseek(fd,-1,SEEK_CUR);		
			// 每一次做完读操作和写操作后指针会自动后移
			// 所以覆盖原来的字符要记得把指针前移一个
			write(fd,&ch,1);
        }else if((ch>=32&&ch<=47)||(ch>=58&&ch<=64)||(ch>=91&&ch<=96)||(ch>=123&&ch<=127)){
            ch = ' ';
            lseek(fd,-1,SEEK_CUR);
            write(fd,&ch,1);
        }
	}
    
    return 0;
}

