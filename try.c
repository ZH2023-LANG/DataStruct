#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100

typedef int ElemType;

typedef struct node
{
    ElemType data;
    struct node *next;
}Node;

// 初始化
Node* initList(){
    Node* head=(Node*)malloc(sizeof(Node));
    head->data=0;
    head->next=NULL;
    return head;
}
// 头插法
int insertHead(Node *L,ElemType e){
    Node *p=(Node*)malloc(sizeof(Node));
    p->data=e;
    p->next=L->next;
    L->next=p;
    return 1;
}
// 尾插法
Node* get_tail(Node *L){
    Node *p=L;
    while (p->next!=NULL)
    {
        p=p->next;
    }
    return p;
}

Node* insertTail(Node *tail,ElemType e){
    Node *p=(Node*)malloc(sizeof(Node));
    p->data=e;
    tail->next=p;
    p->next=NULL;
    return p;
}

void listNode(Node *L){
    Node* p=L->next;
    while (p!=NULL)
    {
        printf("%d\n",p->data);
        p=p->next;
    }
    printf("\n");
}

// 在指定位置插入
int insertNode(Node* L,int pos,ElemType e){
    Node* p=L;
    int i=0;
    while (i<pos-1)
    {
        p=p->next;
        i++;
        if (p==NULL)
        {
            return 0;
        }
    }
    // 要插入的新节点q
    Node* q=(Node*)malloc(sizeof(Node));
    q->data=e;
    q->next=p->next;
    p->next=q;
    return 1;
}
// 删除节点
int deleteNode(Node *L,int pos){
    Node *p=L;
    int i=0;
    // 找到要删除的节点的前驱节点
    while (i<pos-1)
    {
        p=p->next;
        i++;
        if (p==NULL)
        {
            return 0;
        }
    }
    if (p->next==NULL)
    {
        printf("要删除的位置错误\n");
        return 0;
    }
    // 创建q,使其指向即将要删除的节点
    Node *q=p->next;
    p->next=q->next;
    free(q);
    return 0;
}


// 获取链表的长度
int listLength(Node *L){
    // 长度包括了头节点
    Node *p=L;
    int len=0;
    while (p!=NULL)
    {
        p=p->next;
        len++;
    }
    return len;
}

void freelist(Node *L){
    Node *p=L->next;
    Node *q;
    while (p!=NULL)
    {
        q=p->next;
        free(p);
        p=q;
    }
    L->next=NULL;
}


int main(){
    Node *list=initList();
    insertHead(list,10);
    insertHead(list,20);
    insertHead(list,30);
    listNode(list);
    Node* tail=list;
    tail=get_tail(list);
    tail=insertTail(tail,10);
    tail=insertTail(tail,20);
    tail=insertTail(tail,30);
    listNode(list);
    insertNode(list,2,15);
    listNode(list);
    deleteNode(list,2);
    listNode(list);
    int len=listLength(list);
    printf("链表长度是%d\n",len);
    free(list);
    return 0;
}


