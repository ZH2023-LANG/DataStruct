#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct ThreadNode {
    ElemType data;
    struct ThreadNode *lchild;
    struct ThreadNode *rchild;
    int ltag;  // 0: 左孩子  1: 前驱线索
    int rtag;  // 0: 右孩子  1: 后继线索
} ThreadNode;

typedef ThreadNode* ThreadTree;

char str[] = "ABDH##I##EJ###CF##G##";
int idx = 0;

ThreadTree prev = NULL;

// 先序创建二叉树（# 表示空）
void createTree(ThreadTree *T) {
    ElemType ch = str[idx++];

    if (ch == '\0') {   // 防御：串结束
        *T = NULL;
        return;
    }

    if (ch == '#') {
        *T = NULL;
    } else {
        *T = (ThreadTree)malloc(sizeof(ThreadNode));
        if (!*T) {
            perror("malloc");
            exit(1);
        }

        // ✅必须初始化
        (*T)->data = ch;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
        (*T)->ltag = 0;
        (*T)->rtag = 0;

        createTree(&((*T)->lchild));
        createTree(&((*T)->rchild));
    }
}

// 具体线索化（中序线索化核心）
void threading(ThreadTree T) {
    if (T != NULL) {
        // 左子树
        if (T->ltag == 0) threading(T->lchild);

        // 当前结点：处理前驱线索
        if (T->lchild == NULL) {
            T->ltag = 1; 
            T->lchild = prev;
        }

        // 处理 prev 的后继线索
        if (prev != NULL && prev->rchild == NULL) {
            prev->rtag = 1;
            prev->rchild = T;
        }

        prev = T;

        // 右子树
        if (T->rtag == 0) threading(T->rchild);
    }
}

// 开始线索化（带头结点）
void inOrderThreading(ThreadTree *head, ThreadTree T) {
    *head = (ThreadTree)malloc(sizeof(ThreadNode));
    if (!*head) {
        perror("malloc");
        exit(1);
    }

    (*head)->data = '\0';
    (*head)->ltag = 0;
    (*head)->rtag = 1;
    (*head)->rchild = *head;

    if (T == NULL) {
        (*head)->lchild = *head;
        return;
    }

    (*head)->lchild = T;
    prev = *head;

    threading(T);

    // 最后一个结点的后继线索指向 head
    prev->rtag = 1;
    prev->rchild = *head;

    // head 的右指针指向最后一个结点
    (*head)->rchild = prev;
}

// 使用线索进行中序遍历
void inOrder(ThreadTree head) {
    ThreadTree curr = head->lchild;

    while (curr != head) {
        while (curr->ltag == 0) curr = curr->lchild;

        printf("%c ", curr->data);

        while (curr->rtag == 1 && curr->rchild != head) {
            curr = curr->rchild;
            printf("%c ", curr->data);
        }

        curr = curr->rchild;
    }
    printf("\n");
}

int main() {
    ThreadTree T = NULL;
    ThreadTree head = NULL;

    idx = 0;
    createTree(&T);

    inOrderThreading(&head, T);

    inOrder(head);

    return 0;
}
