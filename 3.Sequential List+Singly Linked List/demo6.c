// 找相同的后缀
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

// 创建新节点
Node* newNode(char ch) {
    Node *p = (Node*)malloc(sizeof(Node));
    p->data = ch;
    p->next = NULL;
    return p;
}

// 计算链表长度（带头结点）
int length(Node *head) {
    int len = 0;
    Node *p = head->next;
    while (p) {
        len++;
        p = p->next;
    }
    return len;
}

// 前进 k 步
Node* advance(Node *p, int k) {
    while (k-- > 0 && p) p = p->next;
    return p;
}

// 查找两个链表的公共后缀起点
Node* find_common_tail(Node *str1, Node *str2) {
    Node *p1 = str1->next;
    Node *p2 = str2->next;

    int m = length(str1);
    int n = length(str2);

    if (m > n) p1 = advance(p1, m - n);
    else       p2 = advance(p2, n - m);

    while (p1 && p2 && p1 != p2) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return (p1 == p2) ? p1 : NULL;
}

// 打印链表
void printList(Node *head) {
    for (Node *p = head->next; p; p = p->next)
        printf("%c ", p->data);
    printf("\n");
}

int main() {
    // 1. 构造共享后缀 "i"->"n"->"g"
    Node *i = newNode('i');
    Node *n = newNode('n');
    Node *g = newNode('g');
    i->next = n;
    n->next = g;

    // 2. 构造 "loading" = l->o->a->d->(i)
    Node *head1 = newNode(0);  // 头结点
    Node *l = newNode('l');
    Node *o = newNode('o');
    Node *a = newNode('a');
    Node *d = newNode('d');
    head1->next = l;
    l->next = o;
    o->next = a;
    a->next = d;
    d->next = i;  // 共享后缀

    // 3. 构造 "being" = b->e->(i)
    Node *head2 = newNode(0);  // 头结点
    Node *b = newNode('b');
    Node *e = newNode('e');
    head2->next = b;
    b->next = e;
    e->next = i;  // 共享后缀

    printf("str1: ");
    printList(head1);
    printf("str2: ");
    printList(head2);

    // 4. 查找公共后缀起点
    Node *p = find_common_tail(head1, head2);
    if (p) printf("公共后缀起点：%c\n", p->data);
    else   printf("无公共后缀\n");

    return 0;
}
