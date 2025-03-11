#include <2025Linux.h>

typedef struct shareResource_s{
    int ticketnum;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}shareResource_t;

void *sellWindow(void *arg){
    shareResource_t * pshareRes = (shareResource_t *)arg;

    while(1){
        pthread_mutex_lock(&pshareRes->mutex);
        if(pshareRes->ticketnum<=0){
            pthread_mutex_unlock(&pshareRes->mutex);
            break;
        }
        printf("before sell window, ticketnum = %2d\n",pshareRes->ticketnum);
        pshareRes->ticketnum--;
        printf("after  sell window, ticketnum = %2d\n",pshareRes->ticketnum);
        if(pshareRes->ticketnum<=10){
            pthread_cond_signal(&pshareRes->cond);
        }
        pthread_mutex_unlock(&pshareRes->mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}
void *addWindow(void *arg){
    shareResource_t * pshareRes = (shareResource_t *)arg;
    pthread_mutex_lock(&pshareRes->mutex);
    if(pshareRes->ticketnum > 10){
        printf("ticket is enough now!\n");
        pthread_cond_wait(&pshareRes->cond,&pshareRes->mutex);
    }
    pshareRes->ticketnum += 10;
    printf("add 10 tickets! ticketNum = %d\n",pshareRes->ticketnum);
    pthread_mutex_unlock(&pshareRes->mutex);
    pthread_exit(NULL);
}

int main(int argc,char *argv[])
{
    shareResource_t shareRes;
    shareRes.ticketnum = 20;
    pthread_mutex_init(&shareRes.mutex,NULL);
    pthread_cond_init(&shareRes.cond,NULL);

    pthread_t tid1,tid2,tid3;
    pthread_create(&tid1,NULL,sellWindow,&shareRes);
    pthread_create(&tid2,NULL,sellWindow,&shareRes);
    pthread_create(&tid3,NULL,addWindow,&shareRes);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    
    return 0;
}

