// 线索二叉树
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *l, *r;
    int ltag, rtag; // 0=孩子 1=线索
} Node;

Node* newNode(char x){
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = x; p->l = p->r = NULL;
    p->ltag = p->rtag = 0;
    return p;
}

/* ===== 中序线索化（最核心）===== */
static Node* pre = NULL;

void threadIn(Node* p){
    if(!p) return;

    threadIn(p->l);

    if(p->l == NULL){          // 左空 -> 前驱线索
        p->ltag = 1;
        p->l = pre;
    }
    if(pre && pre->r == NULL){ // pre右空 -> 后继线索
        pre->rtag = 1;
        pre->r = p;
    }
    pre = p;

    threadIn(p->r);
}

/* ===== 线索中序遍历（不递归）===== */
void inorderThread(Node* root){
    Node* p = root;
    while(p && p->ltag==0) p = p->l; // 找最左

    while(p){
        printf("%c ", p->data);

        if(p->rtag==1) p = p->r;     // 线索：直接后继
        else{                         // 孩子：去右子树最左
            p = p->r;
            while(p && p->ltag==0) p = p->l;
        }
    }
}

int main(){
    /* 建树：
          A
         / \
        B   C
       / \   \
      D   E   F
    */
    Node *A=newNode('A'), *B=newNode('B'), *C=newNode('C');
    Node *D=newNode('D'), *E=newNode('E'), *F=newNode('F');

    A->l=B; A->r=C;
    B->l=D; B->r=E;
    C->r=F;

    pre = NULL;
    threadIn(A);

    printf("Threaded inorder: ");
    inorderThread(A);
    printf("\n"); // 输出应为：D B E A C F

    return 0;
}





