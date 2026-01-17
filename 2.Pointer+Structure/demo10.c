// 动态分配内存----结构体
#include <stdio.h>
#include <stdlib.h>
typedef struct 
{
    int x;
    int y;
}po;
int main(){
    po *p;
    p=(po*)malloc(sizeof(po));
    p->x=1;
    p->y=2;
    printf("%d\n",p->x);
    printf("%d\n",p->y);
}