#include <stdio.h>
void print(int j){
    printf("Hello SuYou,j = %d\n",j);
}
int main(int argc,char *argv[])
{
    int arr[3] = {1,2,3};
    int *p = arr;
    *p = 2;
    int j = 10;
    print(j);
    for(int i = 0;i < 5; ++i){
        printf("Hello\n");
    }
    return 0;
}

