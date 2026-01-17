#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct node {
    ElemType data;
    struct node *next;
} Node;

// 查找倒数第k个节点
int findNodeFS(Node *L, int k) {
    Node *fast = L->next;  // 首元结点
    Node *slow = L->next;
    int i;

    // fast先走k步
    for (i = 0; i < k; i++) {
        if (fast == NULL) {
            return 0; // 链表长度小于k
        }
        fast = fast->next;
    }

    // fast和slow同时走，直到fast到达末尾
    while (fast != NULL) {
        fast = fast->next;
        slow = slow->next;
    }

    printf("倒数第%d个节点的值为: %d\n", k, slow->data);
    return 1;
}

// 辅助函数：创建链表
Node* createList(int n) {
    Node *head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    Node *tail = head;
    for (int i = 1; i <= n; i++) {
        Node *p = (Node*)malloc(sizeof(Node));
        p->data = i;
        p->next = NULL;
        tail->next = p;
        tail = p;
    }
    return head;
}

int main() {
    Node *L = createList(5); // 创建一个 1→2→3→4→5 的链表
    int k = 2;
    if (!findNodeFS(L, k))
        printf("查找失败：链表长度小于 %d\n", k);
    return 0;
}

