// 线索二叉树
#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct ThreadNode
{
    ElemType data;
    struct ThreadNode *lchild;
    struct ThreadNode *rchild;
    int ltag;
    int rtag;
}ThreadNode;

typedef ThreadNode* ThreadTree;



