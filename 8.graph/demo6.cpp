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
    Floyd：求“任意两点之间”的最短路径（All-Pairs Shortest Path）

    本函数会计算出：
    1) distance[i][j]：从顶点 i 到顶点 j 的最短距离
    2) path[i][j]     ：从顶点 i 去顶点 j 时，下一步应该走向哪个顶点（next hop）
                         注意：这里的 path 不是“前驱”，而是“下一跳”
                         例如 path[0][8] = 1 表示：v0 去 v8 的第一步先走到 v1

    适用条件：
    - 可以处理有向图/无向图
    - 边权可以为非负（本例是非负）
    - 若存在负权边也可用，但不能有负环（负环会导致最短路无意义）

    时间复杂度：O(n^3)  （n=顶点数）
    空间复杂度：O(n^2)
*/
void floyd(Mat_Graph G)
{
    int path[MAXSIZE][MAXSIZE];       // path[i][j]：i 到 j 的下一跳顶点编号（next hop）
    int distance[MAXSIZE][MAXSIZE];   // distance[i][j]：i 到 j 的最短距离

    /*------------------------------------------------------------
      1) 初始化 distance 和 path 矩阵
      ------------------------------------------------------------
      distance 初始值：直接复制邻接矩阵 G.arc[i][j]
        - 若 i==j，则距离是 0
        - 若 i 和 j 有直接边，则距离是边权
        - 若不可达，则是 MAX（代表无穷大）

      path 初始值：path[i][j] = j
        - 含义：先默认从 i 去 j 的第一步就是走到 j（“直达目标”）
        - 如果将来发现经过某个中转点会更短，就会修改 path[i][j]
    ------------------------------------------------------------*/
    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = 0; j < G.vertex_num; j++)
        {
            distance[i][j] = G.arc[i][j];   // 初始最短路：只考虑直接边

            path[i][j] = j;                 // next-hop 初始化：从 i 去 j 下一步就先去 j
        }
    }

    /*------------------------------------------------------------
      2) Floyd 核心：三重循环不断“尝试加入一个中转点”
      ------------------------------------------------------------
      Floyd 的思想：
        依次把每个点 i 当作“允许经过的中转点”，尝试更新任意两点间的距离。

      下面三层循环含义：
        i：中转点（intermediate vertex / 中间点）
        j：起点（start vertex）
        k：终点（end vertex）

      检查：
        如果走 j -> i -> k 比 j -> k 更短，则更新最短距离和路径信息。

      更新规则（松弛）：
        如果 distance[j][k] > distance[j][i] + distance[i][k]
        那么：
          distance[j][k] = distance[j][i] + distance[i][k]

      路径更新规则（next-hop 版本最关键的一句）：
        path[j][k] = path[j][i]

      为什么是 path[j][i]？
        因为我们把 j->k 的最短路改成了 j->...->i->...->k
        那么从 j 出发去 k 的“第一步”，应该跟从 j 出发去 i 的“第一步”一致
    ------------------------------------------------------------*/
    for (int i = 0; i < G.vertex_num; i++)      // i = 当前允许使用的中转点
    {
        for (int j = 0; j < G.vertex_num; j++)  // j = 起点
        {
            for (int k = 0; k < G.vertex_num; k++)  // k = 终点
            {
                /*------------------------------------------------
                  2.1 不可达情况跳过（非常重要）
                  ------------------------------------------------
                  distance[j][i] >= MAX 表示 j->i 不通
                  distance[i][k] >= MAX 表示 i->k 不通
                  那么 j->i->k 这条路径根本不存在，不能用于更新

                  同时也避免出现 MAX + 某个数 的错误比较/潜在溢出
                ------------------------------------------------*/
                if (distance[j][i] >= MAX || distance[i][k] >= MAX)
                    continue;

                /*------------------------------------------------
                  2.2 尝试松弛：看看经过中转点 i 是否更短
                  ------------------------------------------------*/
                if (distance[j][k] > distance[j][i] + distance[i][k])
                {
                    // 更新最短距离：j->k 变成 j->i->k
                    distance[j][k] = distance[j][i] + distance[i][k];

                    /*--------------------------------------------
                      更新路径（next-hop）
                      --------------------------------------------
                      j->k 的第一步，等于 j->i 的第一步
                      例如：
                        如果 path[j][i] = x
                        说明 j 去 i 的第一步先走到 x
                        那么 j 去 k 的第一步也应该先走到 x
                    --------------------------------------------*/
                    path[j][k] = path[j][i];
                }
            }
        }
    }

    /*------------------------------------------------------------
      3) 输出所有点对的最短距离 + 具体路径
      ------------------------------------------------------------
      这里为了避免无向图打印重复：
        只打印 i < j 的组合（i=0..n-1, j=i+1..n-1）

      路径输出使用 next-hop 回放方式：
        从起点 i 出发，当前点为 cur
        下一跳 = path[cur][j]
        cur = 下一跳
        直到 cur == j（到达终点）
    ------------------------------------------------------------*/
    printf("Floyd All-Pairs Shortest Paths:\n\n");

    for (int i = 0; i < G.vertex_num; i++)
    {
        for (int j = i + 1; j < G.vertex_num; j++)
        {
            // 若不可达，直接输出 unreachable
            if (distance[i][j] >= MAX)
            {
                printf("v%d -> v%d : unreachable\n", i, j);
                continue;
            }

            // 输出最短距离
            printf("v%d -> v%d weight: %d\n", i, j, distance[i][j]);

            // 利用 next-hop 回放并打印路径：v i -> ... -> v j
            int cur = i;                 // 当前所在顶点
            printf("path: v%d", i);      // 先打印起点

            // 不断跳到下一跳，直到到达终点 j
            while (cur != j)
            {
                cur = path[cur][j];      // “去 j 的下一跳”
                printf(" -> v%d", cur);
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