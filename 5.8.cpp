//
// Created by sohne on 2020/12/9.
//

typedef struct GNode *PtrToGNode;
struct GNode {
    int Nv; /* 顶点数 */
    int Ne; /* 边数 */
    AdjList G; /* 邻接表 */
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
    DataType Data; /* 存顶点的数据 */
} AdjList[MaxVertexNum];
/* AdjList是邻接表类型 */

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
    Vertex AdjV; /* 邻接点下标 */
    WeightType Weight; /* 边权重 */
    PtrToAdjVNode Next;
};


//LGraph初始化
// 初始化一个有VertexNum个顶点但没有边的图

typedef int Vertex;
LGraph CreateGraph(int VertexNum){
    Vertex V,W;
    LGraph Graph;

    Graph = (LGraph)malloc(sizeof(struct(GNode)));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    for (V=0;V<Graph->Nv;V++){
        Graph->G[V] = NULL;
    }
    return Graph;
}


void InsertEdge( LGraph Graph, Edge E )
{ PtrToAdjVNode NewNode;
/***************** 插入边 <V1, V2> ****************/
/* 为V2建立新的邻接点 */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
/* 将V2插入V1的表头 */
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
/********** 若是无向图，还要插入边 <V2, V1> **********/
/* 为V1建立新的邻接点 */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;
/* 将V1插入V2的表头 */
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}