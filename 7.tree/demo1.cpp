#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct TreeNode
{
    ElemType data;
    TreeNode *lchild;
    TreeNode *rchild;
}TreeNode;

typedef TreeNode* BiTree;

// 空结点用#
char str[]="ABDH#K###E##CFI###G#J##";
//         A
//       /   \
//      B     C
//    /  \   / \
//   D    E F   G
//  /      /     \
// H      I       J
//  \
//   K

int idx=0;

void createTree(BiTree *T){
    ElemType ch;
    ch=str[idx++];
    if(ch=='#'){
        *T=NULL;
    }else{
        // 1) 先创建当前结点
        *T = (BiTree)malloc(sizeof(TreeNode));
        (*T)->data = ch;

        // 2) 递归创建左子树
        createTree(&((*T)->lchild));

        // 3) 递归创建右子树
        createTree(&((*T)->rchild));
    }
}

//前序遍历
void preOrder(BiTree T){
    if(T==NULL){
        return;
    }
    printf("%c",T->data);
    preOrder(T->lchild);
    preOrder(T->rchild);
}



//中序遍历
void inOrder(BiTree T){
    if(T==NULL){
        return;
    }
    inOrder(T->lchild);
    printf("%c",T->data);
    inOrder(T->rchild);
}


//后序遍历
void postOrder(BiTree T){
    if(T==NULL){
        return;
    }
    postOrder(T->lchild);
    postOrder(T->rchild);
    printf("%c",T->data);
}



int main(){
    BiTree T;
    createTree(&T);
    preOrder(T);   // ABDHKECFIGJ
    printf("\n");
    inOrder(T);   // HKDBEAIFCGJ
    printf("\n");
    postOrder(T); // KHDEBIFJGCA
    printf("\n");
}
