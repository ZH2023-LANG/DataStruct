// 迪杰斯特拉算法
#include <stdio.h>

typedef int VertexType;  //顶点类型
typedef int EdgeType;     //边权类型

#define MAXSIZE 100  // 最多顶点数
#define MAXEDGE 200  //最多边数
#define MAX 0x10000

typedef struct
{
    VertexType vertex[MAXSIZE];  //存顶点编号（这里用 0~8）
    EdgeType arc[MAXSIZE][MAXSIZE];   //邻接矩阵，arc[i][j] = i->j 的边权
    int vertex_num;   //顶点数
    int edge_num;     //边数
} Mat_Graph;


void createGraph(Mat_Graph* G)
{
    G->vertex_num = 9;   // v0 ~ v8 共 9 个点
    G->edge_num = 16;    //  16 条边

    //给每个顶点编号：0~8
    for (int i = 0; i < G->vertex_num; i++)
    {
        G->vertex[i] = i;
    }

    //初始化邻接矩阵
    for (int i = 0; i < G->vertex_num; i++)
    {
        for (int j = 0; j < G->vertex_num; j++)
        {
            if (i == j)
                G->arc[i][j] = 0;  //自己到自己距离为 0
            else
                G->arc[i][j] = MAX;  //先设为 MAX（代表不可达）
        }
    }


    G->arc[0][1] = 1;   // v0-v1 = 1
    G->arc[0][2] = 5;   // v0-v2 = 5

    G->arc[1][2] = 3;   // v1-v2 = 3
    G->arc[1][3] = 7;   // v1-v3 = 7
    G->arc[1][4] = 5;   // v1-v4 = 5

    G->arc[2][4] = 1;   // v2-v4 = 1
    G->arc[2][5] = 7;   // v2-v5 = 7

    G->arc[3][4] = 2;   // v3-v4 = 2
    G->arc[3][6] = 3;   // v3-v6 = 3

    G->arc[4][5] = 3;   // v4-v5 = 3
    G->arc[4][6] = 6;   // v4-v6 = 6
    G->arc[4][7] = 9;   // v4-v7 = 9

    G->arc[5][7] = 5;   // v5-v7 = 5

    G->arc[6][7] = 2;   // v6-v7 = 2
    G->arc[6][8] = 7;   // v6-v8 = 7

    G->arc[7][8] = 4;   // v7-v8 = 4

    for (int i = 0; i < G->vertex_num; i++)
    {
        for (int j = i; j < G->vertex_num; j++)
        {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

/*
    choose：从“尚未确定最短路(found=0)”的顶点里
            选出 distance 最小的那个顶点下标返回
*/
int choose(int distance[], int found[], int vertex_num)
{
    int min = MAX;       // 当前最小距离，初始设为无穷大
    int minPos = -1;     // 最小距离对应的顶点位置

    // 扫描所有点
    for (int i = 0; i < vertex_num; i++)
    {
        // found[i]==0 说明该点还没“定型”
        // distance[i] 小于当前 min，则更新
        if (found[i] == 0 && distance[i] < min)
        {
            min = distance[i];
            minPos = i;
        }
    }
    return minPos; // 返回“本轮要确定”的点
}

/*
    dijkstra：求 begin 到所有点的最短路径
    found[]    ：是否已确定最短路（类似 visited）
    distance[] ：begin 到每个点的当前最短距离
    path[]     ：记录最短路径的前驱，用于还原具体路线
*/
void dijkstra(Mat_Graph G, int begin)
{
    int found[MAXSIZE];    // found[i]=1：表示 i 的最短路已确定
    int path[MAXSIZE];     // path[i]：最短路中 i 的前驱顶点是谁
    int distance[MAXSIZE]; // distance[i]：begin 到 i 的最短距离

    /*
        初始化数组（对应 Dijkstra 表格的第 0/1 行）
        distance[i] = begin 到 i 的直接边权（邻接矩阵的一行）
        found[i]    = 0 表示还未确定
        path[i]     = -1 代表目前没有前驱
    */
    for (int i = 0; i < G.vertex_num; i++)
    {
        found[i] = 0;
        path[i] = -1;

        // 初始最短路：先假设只有“begin -> i”的直接路径
        distance[i] = G.arc[begin][i];

        // 如果 begin 到 i 是可达的（不是 MAX），且 i 不是 begin 本身
        // 那么可以把 begin 设为 i 的前驱
        if (distance[i] < MAX && i != begin)
        {
            path[i] = begin;
        }
    }

    // begin 到 begin 的距离一定是 0
    distance[begin] = 0;

    // begin 自己先定型
    found[begin] = 1;

    /*
        2）主循环：每轮确定一个顶点的最短距离
        共需要确定 vertex_num-1 次（除起点外）
    */
    int next; // next：本轮要确定最短路的点

    for (int i = 1; i < G.vertex_num; i++)
    {
        // 2.1 选出当前“未确定”且距离最小的点 next
        next = choose(distance, found, G.vertex_num);

        // 如果 next == -1，说明剩下的点都不可达
        if (next == -1)
            break;

        // 2.2 将 next 标记为“最短路已确定”
        found[next] = 1;

        /*
            2.3 用 next 去松弛（更新）其他点 j
            松弛含义：
                如果 begin->next + next->j 更短
                就更新 begin->j 的最短距离
        */
        for (int j = 0; j < G.vertex_num; j++)
        {
            // 只更新那些还没定型的点
            if (found[j] == 0)
            {
                // distance[next] + arc[next][j] 表示经过 next 走到 j 的距离
                // 若该距离比当前记录的 distance[j] 更短，则更新
                if (distance[next] + G.arc[next][j] < distance[j])
                {
                    distance[j] = distance[next] + G.arc[next][j];

                    // path[j] = next：说明 j 的最短路径最后一步来自 next
                    // 表格里的 “距离(前驱)” 就对应这里
                    path[j] = next;
                }
            }
        }
    }

    /*
        distance[i]：begin 到 i 的最短距离
        path[i]：i 的前驱点（可用于还原路径）
    */
    printf("Begin = v%d\n\n", begin);

    printf("Vertex : ");
    for (int i = 0; i < G.vertex_num; i++)
        printf("v%-4d", i);

    printf("\nDist   : ");
    for (int i = 0; i < G.vertex_num; i++)
    {
        if (distance[i] >= MAX)
            printf("%-5s", "INF");
        else
            printf("%-5d", distance[i]);
    }

    printf("\nPre    : ");
    for (int i = 0; i < G.vertex_num; i++)
        printf("%-5d", path[i]);

    printf("\n\n");

    /*
        4）打印 begin -> 每个点的实际路径（利用 path[] 回溯）
        方法：
            从终点 t 开始，沿 path[t] 一直回到 begin
            需要用栈（数组模拟）反向输出
    */
    for (int t = 0; t < G.vertex_num; t++)
    {
        // 不可达直接跳过
        if (distance[t] >= MAX)
        {
            printf("v%d -> v%d : unreachable\n", begin, t);
            continue;
        }

        printf("v%d -> v%d (dist=%d): ", begin, t, distance[t]);

        // 用栈存回溯路线
        int stack[MAXSIZE];
        int top = 0;

        int cur = t;
        stack[top++] = cur;

        // 一直回溯到 begin
        while (cur != begin && path[cur] != -1)
        {
            cur = path[cur];
            stack[top++] = cur;
        }

        // 逆序输出路径（因为回溯得到的是终点->起点）
        for (int k = top - 1; k >= 0; k--)
        {
            printf("v%d", stack[k]);
            if (k) printf(" -> ");
        }
        printf("\n");
    }
}

int main(void)
{
    Mat_Graph G;
    createGraph(&G);
    dijkstra(G, 0);

    return 0;
}