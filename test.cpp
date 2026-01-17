#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
 
typedef int ElemType;
 
typedef struct node   //定义单链表的结点类型
{
    ElemType data;  //每个节点存放一个数据元素
    struct node *next;   //指针指向下一个节点
}LNode,*LinkList;       //*LinkList是指向LNode的指针
 
//初始化
int initLinkList(LinkList &L){
    //printf("init....");
    L=(LinkList)malloc(sizeof(LNode));   //分配一个头结点的存储空间，其不存储数据
    if(!L){     //如果为空
        return ERROR;
    }
    L->next=NULL;     //头结点之后暂时没有结点
    return OK;
}
 
//插入
int insertLinkList(LinkList &L,int i,ElemType e){   //i是位序，e是要插入的元素
    //printf("insert...");
    LinkList p=L;        //L指向头结点
    int j=0;             //当前p指向的是第几个结点
    while (p&&j<i-1)     //p不为空,循环找到第i个结点
    {
        p=p->next;
        j++;
    }
    //非法情况
    if (!p||j>i-1)
    {
        return ERROR;
    }
    LinkList q=(LinkList)malloc(sizeof(LNode));
    if(!q){
        return ERROR;
    }
    q->data=e;
    q->next=p->next;   //p的后继指向q的后继
    p->next=q;
    return OK;
}
 
/*尾插法
int insertAtTail(LinkList &L, ElemType e) {
    LinkList p = L, q;
    
    // 查找链表的尾部节点
    while (p->next != NULL) {
        p = p->next;
    }
    // 分配新节点
    q = (LinkList)malloc(sizeof(LNode));
    if (!q) return ERROR;
    q->data = e;
    q->next = NULL; // 新节点的 next 指向空
    p->next = q; // 尾节点指向新节点
    return OK;
}
*/
 
 
//删除，有后继才能删除
int delLinkList(LinkList &L,int i,ElemType &e){      //&e保存将要删除的元素的地址
    //printf("delete...");
    LinkList p=L;   //L指向头结点
    int j=0;
    while (p->next&&j<i-1)
    {
        p=p->next;
        j++;
    }
    //非法情况
    if (!p->next||j>i-1)
    {
        return ERROR;
    }
    LinkList q=p->next; //创建一个新的指针q，让它指向当前节点p的下一个节点(即要删除的节点)
    p->next=q->next;
    e=q->data;
    free(q);
    return OK;
}
 
//访问，！！！！重点，封装操作，提高可扩展性
void printInfo(LinkList L,void (*visit)(ElemType e))   //void为指向函数的指针作为形参，其实参为函数名funPrint
{
    //printf("info...");
    LinkList p=L->next;
    while (p)
    {
        visit(p->data);
        p=p->next;   //往下走直到做完
    }
    
}
//以后要改变输出的内容只要改变这个函数就行了
void funPrint(ElemType e){
    printf("%d\t",e);
}
 
//判断是否为空
int emptyList(LinkList L){
    if (L->next==NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
    return 0;
}
 
//返回它的长度
int lengthList(LinkList L){
    int count = 0;
    LinkList p = L->next;
    while (p) {
        count++;
        p = p->next;
    }
    printf("%d\n",count);
    return count;
}
 
//按值查找元素并返回位序
int findList(LinkList L,ElemType e){        
    LinkList p = L->next;
    int pos = 1;  // 位序从 1 开始计数
 
    while (p) {
        if (p->data == e) {       //查看单链表中有没有哪个值等于e
            printf("%d\n",pos);
            return pos;  // 返回找到的位序
        }
        p = p->next;
        pos++;  // 位序递增
    }
    return ERROR;  // 未找到元素
}
 
int main(){
    LinkList L;   //声明一个指向单链表的指针
    initLinkList(L);
    for (int i = 1; i <=10; i++)
    {
        insertLinkList(L,i,i*10);
    }
    printInfo(L,funPrint);
    printf("\n");
    ElemType e;
    delLinkList(L,5,e);
    printInfo(L,funPrint);
    printf("\n");
    emptyList(L);
    lengthList(L);
    findList(L,60);
    return OK;
}