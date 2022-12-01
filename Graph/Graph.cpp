#include <iostream>
using namespace std;
#define MaxVertexNum 100
#define MaxInt 999
typedef char VertexType;
typedef int ArcType;

typedef struct//邻接矩阵定义
{
    VertexType vexs[MaxVertexNum];  //顶点表
    ArcType arcs[MaxVertexNum][MaxVertexNum];//邻接矩阵
    int vexnum, arcnum;//当前顶点数 边数
}AMGraph;

//邻接表定义

typedef struct ArcNode//边结点定义
{
    int adjvex;              //该边所指向的顶点的位置
    struct ArcNode* nextarc; //指向下一条边的指针
    //OtherInfo info;        //权值
}ArcNode;

typedef struct VNode//顶点信息定义
{
    VertexType data;  //顶点的值
    ArcNode* firstarc;//指针指向第一条依附于该顶点大的边
}VNode,AdjList[MaxVertexNum];

typedef struct //邻接表定义
{
    AdjList vertices;
    int vexnum, arcnum;
}ALGraph;


//辅助函数部分
void CreateUDN(AMGraph& G);//以邻接矩阵方式创建无向图
void CreateUDG(ALGraph& G);//以邻接表方式创建无向图
int LocateVex(AMGraph& G, VertexType v);//返回顶点v在顶点表中的下标
int LocateVex(ALGraph& G, VertexType v);//返回顶点v在顶点表中的下标
void PrintAMGraph(AMGraph& G);//输出邻接矩阵
void PrintALGraph(ALGraph& G);//输出邻接表


int main()
{
   //邻接矩阵法创建无向网
    /*AMGraph G1;
    CreateUDN(G1);//邻接矩阵创建无向图
    PrintAMGraph(G1);//输出邻接矩阵*/


    ALGraph G2;
    CreateUDG(G2);
    PrintALGraph(G2);

}
//辅助函数部分
void CreateUDN(AMGraph& G)//以邻接矩阵方式创建无向图
{
    int i,j,k;
    VertexType vi, vj;//边的两个顶点
    ArcType w;//边的权值
    cout << "请输入待创建图的顶点总数：";
    cin >> G.vexnum;
    cout << "请输入待创建图的边总数：";
    cin >> G.arcnum;
    for ( i = 0; i < G.vexnum; i++) //依次输入各顶点信息
    {
        cout << "请依次输入各顶点信息：";
        cin >> G.vexs[i];
    }
    //cout << "结束了1";
    //初始化邻接矩阵 值全设为最大值（无穷大）
    for ( i = 0; i < G.vexnum; i++)
    {
        for ( j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j] = MaxInt;
            //cout << "结束了2";
        }
    }
    //开始构造邻接矩阵
    for (k = 0; k < G.arcnum; k++)
    {
        cout << "请输入vi、vj及其对应边的权值w:\n";
        cin >> vi >> vj >> w;
        i = LocateVex(G, vi);
        j = LocateVex(G, vj);
        G.arcs[i][j] = w;
        G.arcs[j][i] = w;
    }

}
void CreateUDG(ALGraph& G)//以邻接表方式创建无向图
{
    int i, j, k;
    VertexType vi, vj;//边的两个顶点
    ArcType w;//边的权值
    cout << "请输入待创建图的顶点总数：";
    cin >> G.vexnum;
    cout << "请输入待创建图的边总数：";
    cin >> G.arcnum;
    //输入各顶点信息，创建顶点表（输入各顶点值并将其firstarc置为NULL）
    for (i = 0; i < G.vexnum; i++) 
    {
        cout << "请依次输入各顶点信息：";
        cin >> G.vertices[i].data;  
        G.vertices[i].firstarc = NULL;
    }
    //输入各边，构造邻接表
    for (k = 0; k < G.arcnum; k++)
    {
        cout << "请输入vi、vj\n"; //输入边依附的两顶点
        cin >> vi >> vj;
        i = LocateVex(G, vi);
        j = LocateVex(G, vj);
        //printf("vi所在下标为%d\n",i);
        //printf("vj所在下标为%d\n",j);
        ArcNode* p1 = new ArcNode;
        p1->adjvex = j; //邻接点序号为j
        p1->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p1;  //头插法将*p1插入顶点vi的边表头部\

        ArcNode* p2 = new ArcNode;
        p2->adjvex = i; //邻接点序号为j
        p2->nextarc = G.vertices[j].firstarc;
        G.vertices[j].firstarc = p2;  //头插法将*p1插入顶点vi的边表头部
        
    }
}
int LocateVex(AMGraph& G, VertexType v)
{
    int i;
    
    for ( i = 0; i < G.vexnum; i++)
    {
        if (G.vexs[i] == v)
        {
            return i;
        }

    }
    return - 1;
}
int LocateVex(ALGraph& G, VertexType v)//返回顶点v在顶点表中的下标
{
    int i;
    for ( i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data == v)
            return i;
    }
    return -1;
}
void PrintAMGraph(AMGraph& G)//输出邻接矩阵
{
    int i, j;
    cout << "邻接矩阵如下：" << endl;
    cout << "      ";
    for (i = 0; i < G.vexnum; i++)
    {
        printf("%5c ", G.vexs[i]);
    }
    cout << "" << endl;
    for ( i = 0; i < G.vexnum; i++)
    {
        printf("%5c ", G.vexs[i]);
        for ( j = 0; j <G.vexnum; j++)
        {
            
            printf("%5d ", G.arcs[i][j]);
            
        }
        cout << "" << endl;
    }
}
void PrintALGraph(ALGraph& G)//输出邻接表
{
    int i, j;
    ArcNode* p = NULL;
    for (i = 0; i < G.vexnum; i++)
    {
        printf("[%c]->", G.vertices[i].data);
        p = G.vertices[i].firstarc;
        while (p != NULL)
        {
            printf("[%d|]->",p->adjvex);
            p = p->nextarc;

        }
        cout << "" << endl;
        
    }
    
}