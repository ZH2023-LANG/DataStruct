// 反转链表
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 初始化带头结点的链表
Node* initList(void) {
    Node *head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}

// 创建新节点
Node* newNode(int x) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->data = x;
    p->next = NULL;
    return p;
}

// 尾插
void push_back(Node *L, int x) {
    Node *p = L;
    while (p->next) p = p->next;
    p->next = newNode(x);
}

// 打印链表
void printList(Node *L) {
    Node *p = L->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

/* ---------------- 链表反转核心函数 ---------------- */
Node* reverseList(Node *head) {
    Node *first = NULL;         // 已反转部分的头
    Node *second = head->next;  // 待反转部分
    Node *third;                // 暂存下一节点

    while (second != NULL) {
        third = second->next;   // 暂存 next
        second->next = first;   // 当前节点指向已反转部分
        first = second;         // first 前进
        second = third;         // second 前进
    }

    // 建立新的头结点
    Node *hd = initList();
    hd->next = first;
    return hd;
}

/* ---------------- 测试程序 ---------------- */
int main(void) {
    Node *head = initList();
    push_back(head, 1);
    push_back(head, 2);
    push_back(head, 3);
    push_back(head, 4);
    push_back(head, 5);

    printf("原链表: ");
    printList(head);

    Node *rev = reverseList(head);

    printf("反转后: ");
    printList(rev);

    return 0;
}
