#include <2025Linux.h>

void *threadFunc(void *arg){
    int *fd = (int*)arg;
    char buf[4096];
    read(*fd,buf,sizeof(buf));
    printf("child read main file content:%s\n",buf);
    
}

int main(int argc,char *argv[])
{
    // ./4 file
    ARGS_CHECK(argc,2);
    int fd = open(argv[1],O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,&fd);
    pthread_join(tid,NULL);
    sleep(3);
    printf("main sleep over!\n");
    close(fd);
    return 0;
}

