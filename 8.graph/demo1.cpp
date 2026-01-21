#include <stdio.h>

/*
    VertexType：顶点的数据类型
    这里用 char 存顶点名字：A B C ...
*/
typedef char VertexType;

/*
    EdgeType：边的数据类型
    这里用 int 表示有没有边：
    arc[i][j] = 1 表示 i 和 j 有边
    arc[i][j] = 0 表示没有边
*/
typedef int EdgeType;

#define MAXSIZE 100   // 最大顶点数（预留空间）

/*
    Mat_Grph：邻接矩阵图结构体

    vertex[]  : 存每个顶点的名字（A~I）
    arc[][]   : 邻接矩阵，存边的信息
    vertex_num: 顶点数
    edge_num  : 边数
*/
typedef struct
{
    VertexType vertex[MAXSIZE];
    EdgeType arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
} Mat_Grph;

/*
    visited[]：DFS 用的访问标记数组
    visited[i] = 1 表示顶点 i 已访问过
    visited[i] = 0 表示顶点 i 还没访问
*/
int visited[MAXSIZE];

/*
    create_graph：创建图
*/
void create_graph(Mat_Grph* G)
{
    // 1) 设置顶点数量 和 边数量
    G->vertex_num = 9;
    G->edge_num = 15;

    // 2) 给每个顶点起名字（0~8 分别对应 A~I）
    G->vertex[0] = 'A';
    G->vertex[1] = 'B';
    G->vertex[2] = 'C';
    G->vertex[3] = 'D';
    G->vertex[4] = 'E';
    G->vertex[5] = 'F';
    G->vertex[6] = 'G';
    G->vertex[7] = 'H';
    G->vertex[8] = 'I';

    // 3) 初始化邻接矩阵 arc[][] 全部为 0
    //    表示一开始所有点之间都没有边
    for (int i = 0; i < G->vertex_num; i++)
    {
        for (int j = 0; j < G->vertex_num; j++)
        {
            G->arc[i][j] = 0;
        }
    }

    /*
        注意：这是【无向图】
        所以 u-v 有边，就要同时设置：
            arc[u][v] = 1
            arc[v][u] = 1
    */

    // ===== A-B  A-F =====
    G->arc[0][1] = 1;  G->arc[1][0] = 1;   // A-B
    G->arc[0][5] = 1;  G->arc[5][0] = 1;   // A-F

    // ===== B-C  B-G  B-I =====
    G->arc[1][2] = 1;  G->arc[2][1] = 1;   // B-C
    G->arc[1][6] = 1;  G->arc[6][1] = 1;   // B-G
    G->arc[1][8] = 1;  G->arc[8][1] = 1;   // B-I

    // ===== C-D  C-I =====
    G->arc[2][3] = 1;  G->arc[3][2] = 1;   // C-D
    G->arc[2][8] = 1;  G->arc[8][2] = 1;   // C-I

    // ===== D-E  D-G  D-H  D-I =====
    G->arc[3][4] = 1;  G->arc[4][3] = 1;   // D-E
    G->arc[3][6] = 1;  G->arc[6][3] = 1;   // D-G
    G->arc[3][7] = 1;  G->arc[7][3] = 1;   // D-H
    G->arc[3][8] = 1;  G->arc[8][3] = 1;   // D-I

    // ===== E-F  E-H =====
    G->arc[4][5] = 1;  G->arc[5][4] = 1;   // E-F
    G->arc[4][7] = 1;  G->arc[7][4] = 1;   // E-H
}

/*
    dfs：深度优先遍历函数（递归写法）

    参数：
    G：图（邻接矩阵）
    i：当前访问的顶点下标（0~8）
*/
void dfs(Mat_Grph G, int i)
{
    // 1) 标记当前顶点已访问
    visited[i] = 1;

    // 2) 输出当前顶点名字
    printf("%c\n", G.vertex[i]);

    /*
        3) 扫描 i 这个点能连到哪些点 j
           如果 arc[i][j] == 1 表示 i 和 j 有边
           并且 j 没访问过，就递归继续 DFS(j)
    */
    for (int j = 0; j < G.vertex_num; j++)
    {
        // i 能到 j，并且 j 没走过
        if (G.arc[i][j] == 1 && visited[j] == 0)
        {
            dfs(G, j);   // 继续深入访问 j
        }
    }
}

int main()
{
    Mat_Grph G;

    // 1) 创建图（填顶点和边）
    create_graph(&G);

    // 2) visited 数组清零：表示一开始所有点都没访问
    for (int i = 0; i < G.vertex_num; i++)
    {
        visited[i] = 0;
    }

    // 3) 从 A 开始 DFS
    //    A 的下标是 0
    dfs(G, 0);

    return 0;
}
