#include <2025Linux.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
#define TEST_NUM 10
typedef struct Node{
    int data;
    struct Node *next;
}Node,*LinkList;

void *threadFunc(void *arg){
    LinkList L = (LinkList)arg;
    Node *p=L->next;
    while(p!=NULL){
        printf("%d->",p->data);
        p = p->next;
    }
    printf("NULL\n");
}

void init(LinkList *L){
    for(int i=TEST_NUM;i>0;i--){
        Node *new = (Node*)malloc(sizeof(Node));
        new->data = i;
        new->next = (*L)->next;
        (*L)->next = new;

    }
}

int main(int argc,char *argv[])
{
    LinkList L = (Node *)malloc(sizeof(Node));
    L->next = NULL;
    init(&L);
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc,(LinkList)L);
    pthread_join(tid,NULL);
    sleep(2);
    printf("main sleep over!\n");
    return 0;
}

