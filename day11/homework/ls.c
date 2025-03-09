#include <2025Linux.h>

int main(int argc,char *argv[])
{
    //system("ls");    
	// 目录流
	DIR * dirp = opendir(".");
	struct dirent * direntp;
	while((direntp = readdir(dirp))!=NULL){
		printf("%s\n",direntp->d_name);
	}
	closedir(dirp);
    return 0;
}

