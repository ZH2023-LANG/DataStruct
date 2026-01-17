#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 初始化链表
Node* initList(void) {
    Node *head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    return head;
}

// 尾插
void push_back(Node *L, int x) {
    Node *p = L;
    while (p->next) p = p->next;
    Node *q = (Node*)malloc(sizeof(Node));
    q->data = x;
    q->next = NULL;
    p->next = q;
}

// 打印
void printList(Node *L) {
    Node *p = L->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 删除中间节点
int delMiddleNode(Node *head) {
    if (head == NULL || head->next == NULL) return 0; // 空表
    Node *fast = head->next;
    Node *slow = head;
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node *q = slow->next;
    slow->next = q->next;
    free(q);
    return 1;
}


int main(void) {
    Node *head = initList();
    for (int i = 1; i <= 5; i++)
        push_back(head, i);

    printf("原链表: ");
    printList(head);

    delMiddleNode(head);

    printf("删除中间节点后: ");
    printList(head);

    return 0;
}
