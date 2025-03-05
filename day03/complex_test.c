#include <stdio.h>
void print(int j){
    printf("Hello,I am print,j = %d\n",j);
}
int main(){
    int arr[3] = {1,2,3};
    int j =10;
    int *p=arr;
    p[2]=4;
    print(j);
    for(int i=0;i<5;++i){
        printf("Hello world!!!\n");
    }
}

