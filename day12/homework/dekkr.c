#include <2025Linux.h>
#define NUM 10000000
#define wants_to_enter_0 p[1]
#define wants_to_enter_1 p[2]
#define turn p[3]
#define TRUE 1
#define FALSE 0
int main(int argc,char *argv[])
{
    int shmid = shmget(IPC_PRIVATE,4096,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    int *p = (int *)shmat(shmid,NULL,0);
    //*p = 0; // *p只访问了4个字节
    p[0] = 0;   // *(p+0) 等价于p[0]
    wants_to_enter_0 = FALSE;
    wants_to_enter_1 = FALSE;
    turn = 0;
    if(fork()){
        for(int i = 0;i < NUM;++i){
            wants_to_enter_0 = TRUE;
            while(wants_to_enter_1){
                if(turn!=0){
                    wants_to_enter_0 = FALSE;
                    while(turn!=0);
                    wants_to_enter_0 = TRUE;
                }
            }
            ++p[0];
            turn = 1;
            wants_to_enter_0 = FALSE;
        }
        wait(NULL);
        printf("*p = %d\n",*p);
    }else{
        for(int i = 0;i < NUM;++i){
            wants_to_enter_1 = TRUE;
            while(wants_to_enter_0){
                if(turn!=1){
                    wants_to_enter_1 = FALSE;
                    while(turn!=1);
                    wants_to_enter_1 = TRUE;
                }
            }
            ++p[0];
            turn = 0;
            wants_to_enter_1 = FALSE;
        }
    }
    return 0;
}

