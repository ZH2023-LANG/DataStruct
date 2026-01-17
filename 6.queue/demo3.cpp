#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
//队列结点
typedef struct QueueNode {
    ElemType data;          // 结点里真正存的数据
    struct QueueNode *next; // 指向下一个结点的指针
} QueueNode;
//整个队列结构
typedef struct 
{
    QueueNode *front;
    QueueNode *rear;
}Queue;


//初始化（带头节点）
Queue* initQueue(){
    Queue *q=(Queue*)malloc(sizeof(Queue));
    QueueNode *node=(QueueNode*)malloc(sizeof(QueueNode));
    node->data=0;
    node->next=NULL;
    //队头指针和队尾指针开始都指向头节点
    q->front=node;
    q->rear=node;
    return q;
}


//判空
int isEmpty(Queue *q){
    if(q->front==q->rear){
        return 1;
    }else{
        return 0;
    }
}

//入队(尾插法)
void equeue(Queue *q,ElemType e){
    QueueNode *node=(QueueNode*)malloc(sizeof(QueueNode));
    node->data=e;
    node->next=NULL;
    //把新结点接在原队尾后面。
    q->rear->next=node;
    //把队尾指针挪到新结点上。
    q->rear=node;
}


// 出队
int dequeue(Queue *q,ElemType *e){
    // node 指向真正的队头结点（头节点的下一个结点）
    QueueNode *node=q->front->next;
    // 把要出队的元素值写到 *e 中，带回给调用者
    *e=node->data;
    // 让头结点直接指向原来队头结点的下一个结点，相当于把 node 从链表中断开
    q->front->next=node->next;
    // 如果此时队尾指针刚好也指向这个被删除的结点，说明队列中只有这一个数据结点
    if(q->rear==node){
        // 删除后队列变空，让 rear 重新指向头结点
        q->rear=q->front;
    }
    // 释放被删除结点的内存
    free(node);
    return 1;
}

//获取队头元素
ElemType getFront(Queue *q){
    // 如果队列为空
    if(isEmpty(q)){
        printf("空的");
        return 0;
    }
    // 队列不空时，真正的队头结点在头结点的下一个结点
    return q->front->next->data;
}

int main(){
    Queue *q=initQueue();
    equeue(q,10);
    equeue(q,20);
    equeue(q,30);
    equeue(q,40);
    equeue(q,50);
    ElemType e;
    dequeue(q,&e);
    printf("出队%d\n",e);
    dequeue(q,&e);
    printf("出队%d\n",e);
    printf("%d\n",getFront(q));
}

















