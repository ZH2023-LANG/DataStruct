#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int ElemType;

typedef struct{
    ElemType *data;
    int front;
    int rear;
    
}Queue;

//初始化队列
Queue* initQueue(){
    Queue *q=(Queue*)malloc(sizeof(Queue));
    q->data=(ElemType*)malloc(sizeof(ElemType)*MAXSIZE);
    q->front=0;
    q->rear=0;
    return q;
}

// 判断对列是否为空
int isEmpty(Queue *Q){
    if(Q->front==Q->rear){
        printf("队列为空\n");
        return 1;
    }
    else{
        printf("队列不为空\n");
        return 0;
    }
}


// 入队
int equeue(Queue *Q,ElemType e){
    if((Q->rear+1)%MAXSIZE==Q->front){
        printf("队列满，无法入队\n");
        return 0;
    }
    Q->data[Q->rear]=e;
    Q->rear=(Q->rear+1)%MAXSIZE;
    return 1;
}


//出队
int dequeue(Queue *Q,ElemType *e){
    if(Q->front==Q->rear){
        printf("队列空，无法出队\n");
        return 0;
    }
    //把队头元素拿出来给你
    *e=Q->data[Q->front];
    //把队头指针往后挪一格（循环队列）
    Q->front=(Q->front+1)%MAXSIZE;
    return 1;
}

//获取对头元素
int getHead(Queue *Q,ElemType *e){
    if(Q->front==Q->rear){
        printf("队列空，无法获取队头元素\n");
        return 0;
    }
    *e=Q->data[Q->front];
    return 1;
}


//打印队列元素  
void printQueue(Queue *Q){
    int i=Q->front;
    while(i!=Q->rear){
        printf("%d ",Q->data[i]);
        i=(i+1)%MAXSIZE;
    }
    printf("\n");
}

int main(){
    Queue *q=initQueue();
    equeue(q,10);
    equeue(q,20);
    equeue(q,30);
    equeue(q,40);
    equeue(q,50);
    printQueue(q);
    
    ElemType e;
    dequeue(q,&e);
    printf("出队元素：%d\n",e);
    dequeue(q,&e);
    printf("出队元素：%d\n",e);

    getHead(q,&e);
    printf("队头元素：%d\n",e);

    printQueue(q);
    
    return 0;
}















































