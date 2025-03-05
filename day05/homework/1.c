#include <2025Linux.h>

int main(int argc,char *argv[])
{
    int flag = 0;			// 标记是否找到
    ARGS_CHECK(argc,3);	
	// 切换当前工作目录
    int ret = chdir(argv[1]);
	ERROR_CHECK(ret,-1,"chdir");
	// 获取当前工作目录
	char *cwd = getcwd(NULL,0);
	// 
	DIR *dirp = opendir(".");
    ERROR_CHECK(dirp,NULL,"opendir");
	
    
	struct dirent * direntp;
    while((direntp = readdir(dirp)) != NULL){  // 使用while+readdir依次取出目录项进行比对
        if(strcmp(direntp->d_name, argv[2]) == 0){
            flag = 1;
            printf("abosulte path = %s/%s\n",cwd,direntp->d_name);
        }
    }
    if(!flag){
        printf("File '%s' not found in directory '%s'\n", argv[2], cwd);
    }
    return 0;
}
