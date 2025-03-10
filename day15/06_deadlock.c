#include <2025Linux.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
int main(int argc,char *argv[])
{
    pthread_mutex_lock(&mutex);
    printf("I got lock 1!\n");
    pthread_mutex_lock(&mutex);
    printf("I got lock 2!\n");
    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex);
    return 0;
}

