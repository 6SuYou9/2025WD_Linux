#include <2025Linux.h>

int main(int argc,char *argv[])
{
    if(fork()){
        printf("I am parent.pid = %d,ppid = %d\n",getpid(),getppid());
        int wstatus;
        wait(&wstatus);
        if(WIFEXITED(wstatus)){     // 检查是否是正常退出
            // 获取退出返回值
            printf("exit,ret value = %d\n",WEXITSTATUS(wstatus));
        }else if(WIFSIGNALED(wstatus)){     // 检查是否是异常退出
            // 获取退出信号
            printf("abnormal quit,terminal signal = %d\n",WTERMSIG(wstatus));
        }
    }else{
        printf("I am child.pid = %d,ppid = %d\n",getpid(),getppid());
        while(1){
            sleep(1);
        }
    }
    return 0;
}

