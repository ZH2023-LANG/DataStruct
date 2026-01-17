#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

// 定义链表节点结构
typedef struct node {
    ElemType data;
    struct node *next;
} Node;

// 创建一个空链表（带头结点）
Node* initList() {
    Node *head = (Node*)malloc(sizeof(Node));
    head->next = NULL;
    return head;
}

// 尾插法建立链表
Node* insertTail(Node *head, ElemType e) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->data = e;
    p->next = NULL;

    Node *tail = head;
    while (tail->next != NULL)
        tail = tail->next;

    tail->next = p;
    return head;
}

// 打印链表（最多打印20个，防止死循环）
void printList(Node *head) {
    Node *p = head->next;
    int count = 0;
    while (p != NULL && count < 20) {
        printf("%d -> ", p->data);
        p = p->next;
        count++;
    }
    printf("NULL\n");
}

// 查找环的入口
Node* findBegin(Node *head) {
    Node *fast = head;
    Node *slow = head;

    // 第一步：判断是否有环
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;

        if (fast == slow) {
            // 第二步：计算环的长度
            Node *p = fast;
            int count = 1;
            while (p->next != slow) {
                count++;
                p = p->next;
            }

            // 第三步：寻找环的入口
            fast = head;
            slow = head;
            for (int i = 0; i < count; i++) {
                fast = fast->next;
            }

            while (fast != slow) {
                fast = fast->next;
                slow = slow->next;
            }

            return slow; // 环入口
        }
    }

    return NULL; // 无环
}

int main() {
    // 创建链表
    Node *head = initList();
    for (int i = 1; i <= 6; i++) {
        insertTail(head, i);
    }

    // 手动制造一个环：让最后一个节点指向第3个节点
    Node *p = head->next;
    Node *third = NULL;
    Node *tail = NULL;

    int count = 1;
    while (p != NULL) {
        if (count == 3) third = p; // 记录第3个节点
        if (p->next == NULL) tail = p; // 记录最后一个节点
        p = p->next;
        count++;
    }
    if (tail && third)
        tail->next = third; // 形成环

    // 检测并找到环的入口
    Node *entry = findBegin(head);
    if (entry != NULL)
        printf("链表存在环，入口节点的值为：%d\n", entry->data);
    else
        printf("链表无环。\n");

    return 0;
}
