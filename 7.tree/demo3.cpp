#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct ThreadNode {
    ElemType data;
    struct ThreadNode *lchild;
    struct ThreadNode *rchild;
    int ltag;  // 0: 指向左孩子  1: 指向前驱线索
    int rtag;  // 0: 指向右孩子  1: 指向后继线索
} ThreadNode;

typedef ThreadNode* ThreadTree;

char str[] = "ABDH##I##EJ###CF##G##";
int idx = 0;

ThreadTree prev = NULL; // 线索化时用到的“前驱指针”

// 先序创建二叉树（# 表示空）
void createTree(ThreadTree *T) {
    ElemType ch = str[idx++];

    if (ch == '#') {
        *T = NULL;
    } else {
        *T = (ThreadTree)malloc(sizeof(ThreadNode));
        (*T)->data = ch;

        createTree(&((*T)->lchild));
        if ((*T)->lchild!=NULL)
        {
            (*T)->ltag = 0;
        }
        createTree(&((*T)->rchild));
        if ((*T)->rchild!=NULL)
        {
            (*T)->rtag=0;
        }
    }
}


// 具体线索化
void threading(ThreadTree T){
    if (T!=NULL)
    {
        threading(T->lchild);
        if(T->lchild==NULL){
            T->ltag=1;
            T->lchild=prev;
        }
        if(prev->rchild==NULL){
            prev->rtag=1;
            prev->rchild=T;
        }
        prev=T;
        threading(T->rchild);
    }
    
}

//开始线索化
void inOrderThreading(ThreadTree *head,ThreadTree T){
    //头结点
    *head=(ThreadTree)malloc(sizeof(ThreadNode));
    (*head)->ltag=0;
    (*head)->rtag=1;
    (*head)->rchild=(*head);
    if(T==NULL){
        (*head)->lchild=*head;
    }else{
        (*head)->lchild=T;
        prev=(*head);
        threading(T);
        //最后一个结点线索化
        prev->rchild=*head;
        prev->rtag=1;
        //头结点右孩子指向最后一个结点
        (*head)->rchild=prev;
    }
}

//使用线索进行中序遍历
void inOrder(ThreadTree T){
    ThreadTree curr;
    curr=T->lchild;
    while (curr!=T)
    {
        while (curr->ltag==0)
        {
            curr=curr->lchild;
        }
        printf("%c ",curr->data);
        while (curr->rtag==1 && curr->rchild!=T)    
        {
            curr=curr->rchild;
            printf("%c ",curr->data);
        }
        curr=curr->rchild;
    }
    
}

int main() {
    ThreadTree T;
    ThreadTree head;
    createTree(&T);
    //线索化
    inOrderThreading(&head,T);
    //基于线索遍历
    inOrder(head);

    return 0;
}
