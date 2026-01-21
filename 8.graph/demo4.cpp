#include <stdio.h>
#include <stdlib.h>

typedef char VertexType;
typedef int  EdgeType;

#define MAXSIZE  100
#define MAXEDGE  200
#define MAX      0x7fffffff

// 邻接矩阵图
typedef struct
{
    VertexType vertex[MAXSIZE];
    EdgeType   arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
} Mat_Grph;

// 边（Kruskal 用）
typedef struct
{
    int begin;
    int end;
    int weight;
} Edge;

void create_graph(Mat_Grph* G)
{
    G->vertex_num = 9;
    G->edge_num   = 15;

    G->vertex[0] = 'A';
    G->vertex[1] = 'B';
    G->vertex[2] = 'C';
    G->vertex[3] = 'D';
    G->vertex[4] = 'E';
    G->vertex[5] = 'F';
    G->vertex[6] = 'G';
    G->vertex[7] = 'H';
    G->vertex[8] = 'I';

    // 初始化：对角线0，其余MAX
    for (int i = 0; i < G->vertex_num; i++)
    {
        for (int j = 0; j < G->vertex_num; j++)
        {
            if (i == j) G->arc[i][j] = 0;
            else        G->arc[i][j] = MAX;
        }
    }

    // 赋权（无向图）
    // A-B  A-F
    G->arc[0][1] = 10;
    G->arc[0][5] = 11;

    // B-C  B-G  B-I
    G->arc[1][2] = 18;
    G->arc[1][6] = 16;
    G->arc[1][8] = 12;

    // C-D  C-I
    G->arc[2][3] = 22;
    G->arc[2][8] = 8;

    // D-E  D-G  D-H  D-I
    G->arc[3][4] = 20;
    G->arc[3][6] = 24;
    G->arc[3][7] = 16;
    G->arc[3][8] = 21;

    // E-F  E-H
    G->arc[4][5] = 26;
    G->arc[4][7] = 7;

    // F-G
    G->arc[5][6] = 17;

    // G-H
    G->arc[6][7] = 19;

    // 补成对称（无向图）
    for (int i = 0; i < G->vertex_num; i++)
    {
        for (int j = 0; j < G->vertex_num; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

void swap(Edge* edges, int i, int j)
{
    Edge temp = edges[i];
    edges[i] = edges[j];
    edges[j] = temp;
}

// 你的截图里 sortEdges 就是这种双层循环（类似选择排序/冒泡的变体）
void sortEdges(Edge edges[], int edge_num)
{
    for (int i = 0; i < edge_num; i++)
    {
        for (int j = i + 1; j < edge_num; j++)
        {
            if (edges[i].weight > edges[j].weight)
            {
                swap(edges, i, j);
            }
        }
    }
}

// 并查集：找根
int find(int parent[], int f)
{
    while (parent[f] > 0)
        f = parent[f];
    return f;
}

void Kruskal(Mat_Grph G)
{
    Edge edges[MAXEDGE];
    int k = 0;

    // 1) 从邻接矩阵提取边集（只取 i<j，避免无向边重复）
    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = i + 1; j < G.vertex_num; j++)
        {
            // 注意：必须排除 MAX（无边）和 0（对角线/无意义边）
            if (G.arc[i][j] != MAX && G.arc[i][j] != 0)
            {
                edges[k].begin  = i;
                edges[k].end    = j;
                edges[k].weight = G.arc[i][j];
                k++;
            }
        }
    }

    // 保险：如果你写的 edge_num 和实际提取不一致，就以实际提取 k 为准
    // 否则容易越界或漏边
    int edge_num = k;

    // 2) 按权值排序
    sortEdges(edges, edge_num);

    // 3) 并查集初始化（你的截图是 parent[i] = 0）
    int parent[MAXSIZE];
    for (int i = 0; i < G.vertex_num; i++)
        parent[i] = 0;

    // 4) 依次选边：不成环就加入 MST
    int n, m;
    int total = 0;
    int chosen = 0;

    for (int i = 0; i < edge_num; i++)
    {
        n = find(parent, edges[i].begin);
        m = find(parent, edges[i].end);

        if (n != m)
        {
            parent[n] = m;  // 合并集合（把 n 的根挂到 m 上）

            printf("(%c, %c) %d\n",
                   G.vertex[edges[i].begin],
                   G.vertex[edges[i].end],
                   edges[i].weight);

            total += edges[i].weight;
            chosen++;

            // MST 选到 (V-1) 条边就结束
            if (chosen == G.vertex_num - 1) break;
        }
    }

    printf("Total weight = %d\n", total);
}

int main(int argc, char const *argv[])
{
    Mat_Grph G;
    create_graph(&G);
    Kruskal(G);
    return 0;
}
