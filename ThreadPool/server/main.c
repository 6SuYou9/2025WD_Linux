#include "head.h"   // threadPool_t
#include "worker.h" // tidArr_t
int main(int argc,char *argv[])
{
    threadPool_t threadPool;    // 所有线程池相关的数据都放在threadPool变量中
    tidArrInit(&threadPool.tidArr,3);   // 初始化子线程的tid
    makeWorker(&threadPool); // 创建子线程
    while(1){
        sleep(1);
    }
    return 0;
}

