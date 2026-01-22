// 
#include <stdio.h>

typedef int VertexType;
typedef int EdgeType;

#define MAXSIZE 100
#define MAXEDGE 200
#define MAX 0x10000

typedef struct
{
    VertexType vertex[MAXSIZE];
    EdgeType arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
} Mat_Graph;

void createGraph(Mat_Graph* G)
{
    G->vertex_num = 9;
    G->edge_num = 16;

    for (int i = 0; i < G->vertex_num; i++)
        G->vertex[i] = i;

    for (int i = 0; i < G->vertex_num; i++)
    {
        for (int j = 0; j < G->vertex_num; j++)
        {
            if (i == j) G->arc[i][j] = 0;
            else G->arc[i][j] = MAX;
        }
    }

    G->arc[0][1] = 1;
    G->arc[0][2] = 5;

    G->arc[1][2] = 3;
    G->arc[1][3] = 7;
    G->arc[1][4] = 5;

    G->arc[2][4] = 1;
    G->arc[2][5] = 7;

    G->arc[3][4] = 2;
    G->arc[3][6] = 3;

    G->arc[4][5] = 3;
    G->arc[4][6] = 6;
    G->arc[4][7] = 9;

    G->arc[5][7] = 5;

    G->arc[6][7] = 2;
    G->arc[6][8] = 7;

    G->arc[7][8] = 4;

    // 无向图：补对称
    for (int i = 0; i < G->vertex_num; i++)
    {
        for (int j = i; j < G->vertex_num; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

/*
    Floyd：求任意两点最短路径
    distance[i][j]：i->j 的最短距离
    path[i][j]：从 i 去 j 的“下一跳”顶点（next hop）
*/
void floyd(Mat_Graph G)
{
    int path[MAXSIZE][MAXSIZE];
    int distance[MAXSIZE][MAXSIZE];

    // 1) 初始化
    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = 0; j < G.vertex_num; j++)
        {
            distance[i][j] = G.arc[i][j];

            // next-hop 写法：默认从 i 去 j，下一步就去 j
            path[i][j] = j;
        }
    }

    // 2) 三重循环：中转点 i，起点 j，终点 k（顺序和你截图一致）
    // 注：这里的 i 就是 “中转点”
    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = 0; j < G.vertex_num; j++)
        {
            for (int k = 0; k < G.vertex_num; k++)
            {
                // 不可达就别加，防止 MAX + MAX 溢出/错误比较
                if (distance[j][i] >= MAX || distance[i][k] >= MAX)
                    continue;

                if (distance[j][k] > distance[j][i] + distance[i][k])
                {
                    distance[j][k] = distance[j][i] + distance[i][k];

                    // 关键：j->k 的第一步，等于 j->i 的第一步
                    path[j][k] = path[j][i];
                }
            }
        }
    }

    // 3) 输出最短距离 + 具体路径（按你截图的 while(k!=j) 方式）
    printf("Floyd All-Pairs Shortest Paths:\n\n");

    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = i + 1; j < G.vertex_num; j++)
        {
            if (distance[i][j] >= MAX)
            {
                printf("v%d -> v%d : unreachable\n", i, j);
                continue;
            }

            printf("v%d -> v%d weight: %d\n", i, j, distance[i][j]);

            // 打印路径：i -> ... -> j
            int k = i;
            printf("path: v%d", i);

            // next-hop 回放：不断跳到 path[k][j]
            while (k != j)
            {
                k = path[k][j];
                printf(" -> v%d", k);
            }

            printf("\n\n");
        }
    }
}

int main(void)
{
    Mat_Graph G;
    createGraph(&G);

    // 调用 Floyd
    floyd(G);

    return 0;
}