// Prim 最小生成树（邻接矩阵 + 权值）
#include <stdio.h>
#include <stdlib.h>

typedef char VertexType;
typedef int  EdgeType;

#define MAXSIZE 100
// 把 MAX 定义成一个很大的整数（接近 int 的最大值）
// 把 “没有边” 设置为 MAX,即无穷
#define MAX     0x7fffffff

typedef struct
{
    VertexType vertex[MAXSIZE];
    EdgeType   arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
} Mat_Grph;

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

    // 初始化：对角线为 0，其余为 MAX（表示无边/不可达）
    for (int i = 0; i < G->vertex_num; i++)
    {
        for (int j = 0; j < G->vertex_num; j++)
        {
            if (i == j) G->arc[i][j] = 0;
            else        G->arc[i][j] = MAX;
        }
    }

    // 赋权
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

    // 补成无向图（对称）
    for (int i = 0; i < G->vertex_num; i++)
    {
        for (int j = 0; j < G->vertex_num; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

void prim(Mat_Grph* G)
{
    int i, j, k;
    int min;

    int weight[MAXSIZE];     // 候选边最小权值
    int vex_index[MAXSIZE];  // 值表示出发点，下标表示到达点
    // 从顶点A开始，A一开始就在这棵树里面
    weight[0] = 0;   //vex_index某点与下标对应点的权重
    vex_index[0] = 0;

    // 初始化：先认为都从 0(A) 连过去
    for (i = 1; i < G->vertex_num; i++)
    {
        weight[i] = G->arc[0][i];
        vex_index[i] = 0;
    }

    // 一共选 n-1 条边
    for (i = 1; i < G->vertex_num; i++)
    {
        min = MAX;
        j = 0;
        k = 0;

        // 找到当前 weight 最小且还没加入生成树的顶点 k
        while (j < G->vertex_num)
        {
            if (weight[j] != 0 && weight[j] < min)
            {
                min = weight[j];
                k = j;
            }
            j++;
        }

        // 输出选中的边：vex_index[k] -> k
        printf("(%c, %c)\n", G->vertex[vex_index[k]], G->vertex[k]);

        // 标记 k 已加入生成树（用 weight[k]=0 表示）
        weight[k] = 0;

        // 用新加入的顶点 k 去更新其它顶点的最小候选边
        for (j = 0; j < G->vertex_num; j++)
        {
            if (weight[j] != 0 && G->arc[k][j] < weight[j])
            {
                weight[j] = G->arc[k][j];
                vex_index[j] = k;
            }
        }
    }
}

int main()
{
    Mat_Grph G;
    create_graph(&G);
    prim(&G);
    return 0;
}