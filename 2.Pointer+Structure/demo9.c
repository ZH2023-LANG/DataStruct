// 动态分配内存---数组
#include <stdio.h>
#include <stdlib.h>
int main(){
    int *arr=(int*)malloc(5*sizeof(int));
    for (int  i = 0; i < 5; i++)
    {
        arr[i]=0;
    }
    for (int i = 0; i < 5; i++)
    {
        printf("%d\n",arr[i]);
    }
}