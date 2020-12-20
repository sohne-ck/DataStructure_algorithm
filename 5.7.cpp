//
// Created by sohne on 2020/12/9.
//
#include <iostream>
using namespace std;

typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;
    int Ne;
    weightType G[MaxVertexNum][MaxVertexNum];
    DataType Data[MaxVertexNum];
};
typedef PtrToGNode MGraph;


//初始化一个有VertexNum个顶点但没有边的图
typedef int Vertex;/* 用顶点下标表示顶点,为整型 */
MGraph CreateGraph(int VertexNum){
    Vertex V,W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
    for (v=0;v<Graph->Nv;v++){
        for (w=0;w<Graph->Nv;w++){
            Graph->G[v][w] = 0;
        }
    }
}


//向MGraph中插入边
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1,V2/* 有向边<V1, V2> */
    weightType weight; /* 权重 */
};
typedef PtrToENode Edge;

void InsertEdge(MGraph Graph, Edge E){

    /* 插入边 <V1, V2> */
    Graph->G[E->V1][E->V2] = E->weight;

    /* 若是无向图，还要插入边<V2, V1> */
    Graph->G[E->V2][E->V1] = E->weight;
}

MGraph BuildGraph(){
    MGraph Graph;
    Edge E;
    Vertex V;
    int Nv,i;

    scanf("%d",&Nv);
    Graph = CreateGraph(Nv);
    scanf("%d",&Graph->Ne);
    if (Graph->Ne != 0){
        E = (Edge)malloc(sizeof(ENode));
        for (i=0; i<Graph->Ne; i++ ){
            scanf("%d,%d,%d",&E->V1,&E->V2,&E->weight);
            InsertEdge(Graph,E);
        }
    }
    /* 如果顶点有数据的话，读入数据 */
    for (V=0;V<Graph->Nv;V++){
        scanf("%c",&Graph->Data[V]);
    }
    return Graph;
}



//int G[MAXN][MAXN],Nv,Ne;
//
//void BuildGraph()
//{
//    int i,j,v1,v2,w;
//    scanf("%d",&Nv);
//    /* CreateGraph */
//    for (i=0;i<Nv;i++){
//        for (j=0;j<Nv;j++){
//            G[i][j] = 0; /*或INFINITY */
//        }
//    }
//    scanf("%d",&Ne);
//    for (i=0;i<Ne;i++){
//        scanf("%d %d %d",&v1,&v2,&w);
//        G[v1][v2] = w;
//        G[v2][v1] = w;
//    }
//}


