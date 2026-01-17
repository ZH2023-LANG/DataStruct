// 双向链表
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct node
{
    ElemType data;
    struct node *prev,*next;
}Node;


// 初始化链表
Node* initList(){
    Node *head=(Node*)malloc(sizeof(Node));
    head->data=0;
    head->next=NULL;
    head->prev=NULL;
    return head;
}

// 头插法
// 在 双向链表 的 头结点 L 之后，插入一个新节点 p
int insertHead(Node* L,ElemType e){
    Node *p=(Node*)malloc(sizeof(Node));
    p->data=e;
    p->prev=L;
    p->next=L->next;
// 如果原本链表不为空（也就是 头节点L之后确实还有节点），
// 那么原来第一个节点（即 L->next）的 prev 指针，
// 要从原来的 L 改成现在的 p
    if (L->next!=NULL)
    {
        L->next->prev=p;
    }
    L->next=p;
    return 1;
}

// 遍历
void listNode(Node* L){
      Node *p=L->next;
      while (p!=NULL)
      {
        printf("%d ",p->data);
        p=p->next;
      }
      printf("\n");
}
// 获取尾部节点
Node* get_tail(Node *L){
    Node *p=L;
    while (p->next!=NULL)
    {
        p=p->next;
    }
    return p;
}
// 尾插法
Node* insertTail(Node *tail,ElemType e){
    Node *p=(Node*)malloc(sizeof(Node));
    p->data=e;
    p->prev=tail;
    tail->next=p;
    p->next=NULL;
    return p;
}
// 指定位置插入
int insertNode(Node *L,int pos,ElemType e){
    Node *p=L;
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
    Node *q= (Node*)malloc(sizeof(Node));
    q->data=e;
    q->prev=p;
    q->next=p->next;
    p->next->prev=q;
    p->next=q;
    return 1;
}

// 删除节点
int deleteNode(Node *L,int pos){
    Node *p=L;
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
    if (p->next==NULL)
    {
        printf("要删除的位置错误\n");
        return 0;
    }
    Node *q=p->next;
    p->next=q->next;
    q->next->prev=p;
    free(q);
    return 1;
}

// 释放链表
void freeList(Node *L){
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

    Node *tail=get_tail(list);
    tail=insertTail(tail,10);
    tail=insertTail(tail,20);
    tail=insertTail(tail,30);
    listNode(list);

    insertNode(list,2,15);
    listNode(list);

    deleteNode(list,2);
    listNode(list);
}

