#include <stdio.h>
#include <stdlib.h>   // malloc, free
#include <math.h>     // abs

typedef struct Node {
    int data;
    struct Node *next;
} Node;

/* 带头结点初始化 */
Node* initList(void){
    Node *head = (Node*)malloc(sizeof(Node));
    head->data = 0;
    head->next = NULL;
    return head;
}

/* 新结点 */
Node* newNode(int x){
    Node *p = (Node*)malloc(sizeof(Node));
    p->data = x;
    p->next = NULL;
    return p;
}

/* 尾插（演示用） */
void push_back(Node *L, int x){
    Node *p = L;
    while (p->next) p = p->next;
    p->next = newNode(x);
}

/* 打印（不含头结点） */
void printList(Node *L){
    for (Node *p = L->next; p; p = p->next) printf("%d ", p->data);
    printf("\n");
}

/* ---------- 关键：删除绝对值相同(仅保留首次出现) ---------- */
/* 参数 n 是 |data| 的上界（题设给定或可由输入得知） */
void removeNode(Node *L, int n){
    Node *p = L;                                // p 为前驱，从头结点开始
    int *seen = (int*)malloc(sizeof(int) * (n + 1));
    if (!seen) return;

    // 初始化标记数组
    for (int i = 0; i <= n; ++i) seen[i] = 0;

    while (p->next != NULL){
        int index = abs(p->next->data);         // 取绝对值
        if (seen[index] == 0){                  // 首次出现，做标记并前进
            seen[index] = 1;
            p = p->next;
        }else{                                  // 重复 -> 删除 p->next
            Node *temp = p->next;
            p->next = temp->next;
            free(temp);
        }
    }
    free(seen);
}

/* 演示：题目示例 */
int main(void){
    // head: 21 -> -15 -> -15 -> -7 -> 15
    Node *head = initList();
    push_back(head, 21);
    push_back(head, -15);
    push_back(head, -15);
    push_back(head, -7);
    push_back(head, 15);

    printf("原链表: ");
    printList(head);

    removeNode(head, 21);   // n 取绝对值上界（本例为 21）

    printf("删除后: ");
    printList(head);        // 期望输出：21 -15 -7
    return 0;
}