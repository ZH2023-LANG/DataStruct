// 栈的顺序结构的初始化--动态内存分配
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int ElemType;
typedef struct 
{
    ElemType *data;
    int top;
}Stack;

Stack* initStack(){
    Stack *s=(Stack*)malloc(sizeof(Stack));
    s->data=(ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
    s->top=-1;
    return s;
}
