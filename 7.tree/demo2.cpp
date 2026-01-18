#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
typedef char ElemType;

typedef struct TreeNode {
    ElemType data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode;

typedef TreeNode* BiTree;

/* 栈里存 BiTree（结点指针） */
typedef struct {
    BiTree data[MAXSIZE];
    int top; // -1 表示空
} Stack;

void initStack(Stack *s) { s->top = -1; }

int isEmpty(Stack *s) { return s->top == -1; }

int push(Stack *s, BiTree x) {
    if (s->top == MAXSIZE - 1) return 0;
    s->data[++s->top] = x;
    return 1;
}

int pop(Stack *s, BiTree *x) {
    if (isEmpty(s)) return 0;
    *x = s->data[s->top--];
    return 1;
}

/* 创建一个新结点 */
BiTree newNode(ElemType x) {
    BiTree p = (BiTree)malloc(sizeof(TreeNode));
    p->data = x;
    p->lchild = NULL;
    p->rchild = NULL;
    return p;
}

/* 递归中序 */
void inOrder(BiTree T) {
    if (T == NULL) return;
    inOrder(T->lchild);
    printf("%c ", T->data);
    inOrder(T->rchild);
}

/* 非递归前序：根-左-右 */
void iterPreOrder(Stack *s, BiTree T) {
    while (T != NULL || !isEmpty(s)) {
        while (T != NULL) {
            printf("%c ", T->data);  // 访问根
            push(s, T);              // 根入栈，回来走右子树
            T = T->lchild;           // 一路向左
        }
        pop(s, &T);                  // 回退到最近祖先
        T = T->rchild;               // 转向右子树
    }
}

/* 释放二叉树 */
void freeTree(BiTree T) {
    if (T == NULL) return;
    freeTree(T->lchild);
    freeTree(T->rchild);
    free(T);
}

int main() {
    /*
          A
         / \
        B   C
       / \   \
      D   E   F
    */

    BiTree A = newNode('A');
    BiTree B = newNode('B');
    BiTree C = newNode('C');
    BiTree D = newNode('D');
    BiTree E = newNode('E');
    BiTree F = newNode('F');

    A->lchild = B;
    A->rchild = C;
    B->lchild = D;
    B->rchild = E;
    C->rchild = F;

    printf("递归中序遍历: ");
    inOrder(A);
    printf("\n");

    Stack s;
    initStack(&s);

    printf("非递归前序遍历: ");
    iterPreOrder(&s, A);
    printf("\n");

    freeTree(A);
    return 0;
}
