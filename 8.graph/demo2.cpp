//广度优先搜索
#include <stdio.h>

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100

typedef struct
{
    VertexType vertex[MAXSIZE];
    EdgeType arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
} Mat_Grph;

int visited[MAXSIZE];

void create_graph(Mat_Grph* G)
{
    G->vertex_num = 9;
    G->edge_num = 15;

    G->vertex[0] = 'A';
    G->vertex[1] = 'B';
    G->vertex[2] = 'C';
    G->vertex[3] = 'D';
    G->vertex[4] = 'E';
    G->vertex[5] = 'F';
    G->vertex[6] = 'G';
    G->vertex[7] = 'H';
    G->vertex[8] = 'I';

    for (int i = 0; i < G->vertex_num; i++)
        for (int j = 0; j < G->vertex_num; j++)
            G->arc[i][j] = 0;

    G->arc[0][1] = 1;    // A-B
    G->arc[0][5] = 1;    // A-F

    G->arc[1][2] = 1;    // B-C
    G->arc[1][6] = 1;    // B-G
    G->arc[1][8] = 1;    // B-I

    G->arc[2][3] = 1;    // C-D
    G->arc[2][8] = 1;    // C-I

    G->arc[3][4] = 1;    // D-E
    G->arc[3][6] = 1;    // D-G
    G->arc[3][7] = 1;    // D-H
    G->arc[3][8] = 1;    // D-I

    G->arc[4][5] = 1;    // E-F
    G->arc[4][7] = 1;    // E-H

    G->arc[5][6] = 1;    // F-G
    G->arc[6][7] = 1;    // G-H

    // 补成无向图（对称）
    for (int i = 0; i < G->vertex_num; i++)
        for (int j = 0; j < G->vertex_num; j++)
            if (G->arc[i][j] == 1) G->arc[j][i] = 1;
}

// 广度优先遍历 BFS
// 参数：G 是图（邻接矩阵），i 是起点下标（比如 0 表示 A）
// BFS：广度优先搜索（从 start 开始遍历图）
void bfs(Mat_Grph G, int start)
{
    int queue[MAXSIZE];      // 用数组模拟“队列”
    int front = 0, rear = 0; // front：队头下标
                             // rear ：队尾下标

    //先访问起点 start 
    visited[start] = 1;              // 标记 start 已访问（防止重复访问）
    printf("%c\n", G.vertex[start]); 

    // 起点入队
    queue[rear++] = start;  // 把 start 放进队列尾部，然后 rear 往后移动一格

    // 只要队列不为空，就一直循环
    // front == rear 表示队列为空
    while (front != rear)
    {
        //出队一个顶点 u
        // 取出队头元素 queue[front]，然后 front 往后移一格
        int u = queue[front++];

        //扫描 u 的所有邻接点 v 
        // 因为是邻接矩阵，所以要把 v 从 0 扫到 vertex_num-1
        for (int v = 0; v < G.vertex_num; v++)
        {
            // 如果 u 和 v 之间有边（arc[u][v] == 1）
            // 并且 v 还没有访问过（visited[v] == 0）
            if (G.arc[u][v] == 1 && visited[v] == 0)
            {
                // ===== 发现一个“新点 v” =====
                visited[v] = 1;     // 先标记已访问,避免重复入队
                printf("%c\n", G.vertex[v]); // 输出 v（表示访问到它）

                //  v 入队
                // v 将来会作为 u 一样，从队列中出队，再扩展它的邻居
                queue[rear++] = v;
            }
        }
    }
}


int main()
{
    Mat_Grph G;
    create_graph(&G);

    for (int i = 0; i < G.vertex_num; i++)
        visited[i] = 0;

    // 从 A(0) 开始 BFS
    bfs(G,0);

    return 0;
}






