#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

typedef int ElemType;

typedef struct 
{
    ElemType *data;
    int length;
}SeqList;

SeqList* initList(){
    SeqList *L=(SeqList*)malloc(sizeof(SeqList));
    L->data=(ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
    L->length=0;
    return L;
}
int main(){
    // 声明一个线性表并初始化
    SeqList *list=initList();
}