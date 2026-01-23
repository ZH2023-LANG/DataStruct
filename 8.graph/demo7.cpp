//拓扑排序
#include <stdio.h>
#include <stdlib.h>

typedef int VertexType;
typedef int EdgeType;

#define MAXSIZE 100

// 邻接矩阵图
typedef struct {
    VertexType vertex[MAXSIZE];
    EdgeType arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
} Mat_Graph;

// 邻接表边结点
typedef struct EdgeNode {
    int edge_vex;              // 指向的顶点下标
    struct EdgeNode* next;
} EdgeNode;

// 邻接表顶点结点
typedef struct VertexNode {
    int data;                  // 顶点信息
    int in;                    // 入度
    EdgeNode* head;            // 边表头指针
} VertexNode;

typedef VertexNode Adj_List[MAXSIZE];

// 邻接表图
typedef struct {
    Adj_List adj_list;
    int vertex_num;
    int edge_num;
} Adj_Graph;

typedef Adj_Graph* Adj_List_Graph;

// ---------------- 栈（用于存放入度为0的点） ----------------
int top = -1;
int stack[MAXSIZE];

void push(int e) {
    if (top >= MAXSIZE - 1) {
        printf("栈满了\n");
        return;
    }
    top++;
    stack[top] = e;
}

int pop(void) {
    if (top == -1) {
        printf("栈空的\n");
        return -1;
    }
    int elem = stack[top];
    top--;
    return elem;
}

int is_empty(void) {
    return top == -1;
}

// ---------------- 构造示例图（邻接矩阵） ----------------
void create_graph(Mat_Graph* G) {
    G->vertex_num = 14;
    G->edge_num = 20;

    for (int i = 0; i < G->vertex_num; i++) {
        G->vertex[i] = i;
    }

    for (int i = 0; i < G->vertex_num; i++) {
        for (int j = 0; j < G->vertex_num; j++) {
            G->arc[i][j] = 0;
        }
    }

    // 20 条有向边（DAG）
    G->arc[0][4]  = 1;
    G->arc[0][5]  = 1;
    G->arc[0][7]  = 1;
    G->arc[0][11] = 1;

    G->arc[1][2]  = 1;
    G->arc[1][4]  = 1;
    G->arc[1][8]  = 1;

    G->arc[2][5]  = 1;
    G->arc[2][6]  = 1;
    G->arc[2][9]  = 1;

    G->arc[3][2]  = 1;
    G->arc[3][13] = 1;

    G->arc[6][5]  = 1;

    G->arc[5][8]  = 1;
    G->arc[5][12] = 1;

    G->arc[8][7]  = 1;

    G->arc[12][9] = 1;

    G->arc[9][10] = 1;
    G->arc[9][11] = 1;

    G->arc[10][13] = 1;

}

// ---------------- 邻接矩阵 -> 邻接表，并统计入度 ----------------
void create_adj_graph(Mat_Graph G, Adj_List_Graph* ALG) {
    *ALG = (Adj_List_Graph)malloc(sizeof(Adj_Graph));
    if (*ALG == NULL) {
        printf("malloc failed\n");
        exit(1);
    }

    (*ALG)->vertex_num = G.vertex_num;
    (*ALG)->edge_num = G.edge_num;

    for (int i = 0; i < G.vertex_num; i++) {
        (*ALG)->adj_list[i].in = 0;
        (*ALG)->adj_list[i].data = G.vertex[i];
        (*ALG)->adj_list[i].head = NULL;
    }

    for (int i = 0; i < G.vertex_num; i++) {
        for (int j = 0; j < G.vertex_num; j++) {
            if (G.arc[i][j] == 1) {
                EdgeNode* e = (EdgeNode*)malloc(sizeof(EdgeNode));
                e->edge_vex = j;
                e->next = (*ALG)->adj_list[i].head;
                (*ALG)->adj_list[i].head = e;

                (*ALG)->adj_list[j].in++; // j 的入度+1
            }
        }
    }
}

// ---------------- 拓扑排序（Kahn：入度为0入栈） ----------------
void topological_sort(Adj_List_Graph ALG) {
    // 初始化：把所有入度为0的点入栈
    for (int i = 0; i < ALG->vertex_num; i++) {
        if (ALG->adj_list[i].in == 0) {
            push(i);
        }
    }

    int count = 0;

    while (!is_empty()) {
        int curr = pop();
        if (curr == -1) break;

        printf("%d", ALG->adj_list[curr].data);
        count++;
        if (count < ALG->vertex_num) printf(" -> ");

        // “删除”curr 的所有出边：让其邻接点入度--
        EdgeNode* e = ALG->adj_list[curr].head;
        while (e != NULL) {
            int k = e->edge_vex;
            ALG->adj_list[k].in--;
            if (ALG->adj_list[k].in == 0) {
                push(k);
            }
            e = e->next;
        }
    }

    if (count < ALG->vertex_num) {
        printf("\n图中有环,无法拓扑排序!\n");
    } else {
        printf("\n");
    }
}

// ---------------- 释放邻接表内存 ----------------
void free_adj_graph(Adj_List_Graph ALG) {
    if (!ALG) return;
    for (int i = 0; i < ALG->vertex_num; i++) {
        EdgeNode* p = ALG->adj_list[i].head;
        while (p) {
            EdgeNode* tmp = p;
            p = p->next;
            free(tmp);
        }
        ALG->adj_list[i].head = NULL;
    }
    free(ALG);
}

int main(void) {
    Mat_Graph G;
    Adj_List_Graph ALG;

    create_graph(&G);
    create_adj_graph(G, &ALG);

    topological_sort(ALG);

    free_adj_graph(ALG);
    return 0;
}