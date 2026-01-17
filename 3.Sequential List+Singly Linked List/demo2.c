#include <stdio.h>
#define MAXSIZE 100    

typedef int ElemType; 

typedef struct {
    ElemType data[MAXSIZE];  
    int length;              
} SeqList;


// 初始化
void initList(SeqList *L){
    L->length=0;
}

// 遍历
void listElem(SeqList *L){
    for (int i = 0; i < L->length;i++)
    {
        printf("%d ",L->data[i]);
    }
    printf("\n");
}

// 尾部增加元素
int appendElem(SeqList *L,ElemType e){
    if (L->length>=MAXSIZE)
    {
        printf("顺序表已满\n");
        return 0;
    }
    L->data[L->length]=e;
    L->length++;
    return 1;
}

// 往指定位置插入元素
int insertElem(SeqList *L,int pos,ElemType e){
    if (L->length>=MAXSIZE)
    {
        printf("表已经满了\n");
        return 0;
    }
    if (pos<1||pos>L->length)
    {
        printf("插入位置错误");
        return 0;
    }   
    if (pos<= L->length)
    {
        for (int i = L->length-1; i >= pos-1; i--)
        {
            L->data[i+1]=L->data[i];
        }
        L->data[pos-1]=e;
        L->length++;
    }
    return 1;
}

// 删除指定位置的元素
int deleteElem(SeqList *L,int pos,ElemType *e){
    if (L->length==0)
    {
        printf("空表\n");
        return 0;
    }
    if (pos<1||pos>L->length)
    {
        printf("删除数据位置有误\n");
        return 0;
    }
    
    *e=L->data[pos-1];
    if (pos<L->length)
    {
        for (int i = pos; i < L->length;i++ )
        {
            L->data[i-1]=L->data[i];
        }
    }
    L->length--;
    return 1;
}

// 查找元素
int findElem(SeqList *L,ElemType e){
    if (L->length==0)
    {
        printf("空列表\n");
        return 0;
    }
    
    for (int i = 0; i < L->length;i++ )
    {
        if (L->data[i]==e)
        {
            return i+1;
        }
    }
    return 0;
}


int main(){
    // 声明一个线性表并初始化
    SeqList list;
    initList(&list);
    printf("初始化完成，目前长度占用%d\n",list.length);
    printf("目前占用内存%zu字节\n",sizeof(list.data));
    appendElem(&list,1);
    appendElem(&list,2);
    appendElem(&list,3);
    appendElem(&list,4);
    listElem(&list);
    insertElem(&list,2,18);
    listElem(&list);
    ElemType delData;
    // 删除第二个位置的元素
    deleteElem(&list,2,&delData);
    listElem(&list);
    printf("%d\n",findElem(&list,1));
}