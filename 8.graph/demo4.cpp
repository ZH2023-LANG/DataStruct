// 克鲁斯卡尔（Kruskal）

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

// 边结构（用于 Kruskal）
typedef struct
{
    int begin;
    int end;
    int weight;
} Edge;

// 创建图（A~I，15条边）
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

// 交换两条边（排序用）
void swap(Edge* edges, int i, int j)
{
    Edge temp = edges[i];
    edges[i] = edges[j];
    edges[j] = temp;
}

// 简单冒泡排序（按权值从小到大）
void sort_edges(Edge* edges, int edge_num)
{
    for (int i = 0; i < edge_num - 1; i++)
    {
        for (int j = 0; j < edge_num - 1 - i; j++)
        {
            if (edges[j].weight > edges[j + 1].weight)
            {
                swap(edges, j, j + 1);
            }
        }
    }
}

// 并查集：查找根
int find(int* parent, int f)
{
    while (parent[f] > 0)
        f = parent[f];
    return f;
}

// 从邻接矩阵提取边集（只取 i<j 防止重复）
void get_edges(Mat_Grph G, Edge* edges)
{
    int k = 0;
    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = i + 1; j < G.vertex_num; j++)
        {
            if (G.arc[i][j] != MAX && G.arc[i][j] != 0)
            {
                edges[k].begin  = i;
                edges[k].end    = j;
                edges[k].weight = G.arc[i][j];
                k++;
            }
        }
    }
}

// Kruskal 最小生成树
void Kruskal(Mat_Grph G)
{
    int parent[MAXSIZE] = {0};
    Edge edges[MAXEDGE];

    // 1）提取边集
    get_edges(G, edges);

    // 2）排序边（从小到大）
    sort_edges(edges, G.edge_num);

    // 3）依次选边（并查集判断是否成环）
    for (int i = 0; i < G.edge_num; i++)
    {
        int n = find(parent, edges[i].begin);
        int m = find(parent, edges[i].end);

        if (n != m) // 不在同一个集合 → 不成环 → 选这条边
        {
            parent[n] = m;
            printf("(%c, %c) %d\n",
                   G.vertex[edges[i].begin],
                   G.vertex[edges[i].end],
                   edges[i].weight);
        }
    }
}

int main()
{
    Mat_Grph G;
    create_graph(&G);
    Kruskal(G);
    return 0;
}







