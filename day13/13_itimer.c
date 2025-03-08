#include <2025Linux.h>
#include <sys/time.h>
void handler(int signum){
    printf("signum = %d\n",signum);
    time_t now = time(NULL);
    printf("now = %s\n",ctime(&now));
}
int main(int argc,char *argv[])
{
    //signal(SIGALRM,handler);
    signal(SIGPROF,handler);
    handler(0);
    struct itimerval timer;
    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;
    timer.it_interval.tv_usec = 0;

    //setitimer(ITIMER_REAL,&timer,NULL);
    setitimer(ITIMER_PROF,&timer,NULL);
    while(1);
    return 0;
}

