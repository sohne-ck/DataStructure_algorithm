#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INFINITY 65535
#define ERROR -1
/* ����������������ͼ���ڽӱ��忪ʼ������������ */
#define MaxVertexNum 500
typedef int Vertex;
typedef int WeightType;
typedef int DataType;

typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;
    WeightType RoadLength;  // ·�ĳ���
};
typedef PtrToENode Edge;

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
    Vertex AdjV;
    WeightType RoadLength;  // ·�ĳ���
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
    DataType RescueNum;     // ���ȶ�����
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph CreateGraph( int VertexNum );
void DestoryGraph( LGraph Graph );
void InsertEdge(LGraph Graph, Edge E);
/* ����������������ͼ���ڽӱ������������������ */
Vertex source, destination;
bool collected[MaxVertexNum];   // �Ƿ���¼
WeightType roadLength[MaxVertexNum];    // ·������
int shortestNum[MaxVertexNum];  // ���·����
DataType rescueNum[MaxVertexNum];   // ���ȶ�����

LGraph BuildGraph();
void init(LGraph Graph);
int FindMinDist(LGraph Graph);
void solve(LGraph Graph);

int main()
{
    LGraph graph;
    graph = BuildGraph();
    solve(graph);
    DestoryGraph(graph);

    return 0;
}

LGraph CreateGraph( int VertexNum )
{
    Vertex V;
    LGraph Graph;

    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    for (V = 0; V < Graph->Nv; ++V)
        Graph->G[V].FirstEdge = NULL;

    return Graph;
}

void DestoryGraph( LGraph Graph )
{
    Vertex V;
    PtrToAdjVNode Node;
    for (V = 0; V < Graph->Nv; ++V) {
        while (Graph->G[V].FirstEdge) {
            Node = Graph->G[V].FirstEdge;
            Graph->G[V].FirstEdge = Node->Next;
            free(Node);
        }
    }
    free(Graph);
}

void InsertEdge(LGraph Graph, Edge E)
{
    PtrToAdjVNode NewNode;

    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2; NewNode->RoadLength = E->RoadLength;
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;

    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1; NewNode->RoadLength = E->RoadLength;
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildGraph()
{
    LGraph graph;
    Edge E;
    Vertex V;
    int Nv, i;

    scanf("%d", &Nv);
    graph = CreateGraph(Nv);
    scanf("%d", &(graph->Ne));
    scanf("%d %d", &source, &destination);
    for (V = 0; V < Nv; ++V)
        scanf("%d", &(graph->G[V].RescueNum));
    if (graph->Ne != 0) {
        E = (Edge)malloc(sizeof(struct ENode));
        for (i = 0; i < graph->Ne; ++i) {
            scanf("%d %d %d", &(E->V1), &(E->V2), &(E->RoadLength));
            InsertEdge(graph, E);
        }
        free(E);
    }

    return graph;
}

void init(LGraph Graph)
{
    Vertex V;
    for (V = 0; V < Graph->Nv; ++V) {
        collected[V] = false;
        roadLength[V] = INFINITY;
        shortestNum[V] = 0;
    }
}

int FindMinDist(LGraph Graph)
{
    Vertex MinV, V;
    int MinDist = INFINITY;

    for (V = 0; V < Graph->Nv; ++V) {
        if (!collected[V] && roadLength[V] < MinDist) {
            MinDist = roadLength[V];
            MinV = V;
        }
    }
    if (MinDist < INFINITY) return MinV;
    else return ERROR;
}

void solve(LGraph Graph)
{
    PtrToAdjVNode edge;
    Vertex V;

    init(Graph);
    // �Ƚ�Դ�������ȡԪ�صļ����У�Ȼ��������ڽӵ����ֵ
    collected[source] = true; roadLength[source] = 0;
    shortestNum[source] = 1; rescueNum[source] = Graph->G[source].RescueNum;
    for (edge = Graph->G[source].FirstEdge; edge; edge = edge->Next) {
        roadLength[edge->AdjV] = edge->RoadLength;
        shortestNum[edge->AdjV] = shortestNum[source];
        rescueNum[edge->AdjV] = rescueNum[source] + Graph->G[edge->AdjV].RescueNum;
    }
    // Ȼ�����δ�δȡԪ�����Ҿ�����С��Ԫ�ط��뼯����
    while (true) {
        V = FindMinDist(Graph);
        if (V == ERROR || V == destination)
            break;
        collected[V] = true;
        for (edge = Graph->G[V].FirstEdge; edge; edge = edge->Next) {
            if (!collected[edge->AdjV]) {
                if (roadLength[V] + edge->RoadLength < roadLength[edge->AdjV]) {
                    roadLength[edge->AdjV] = roadLength[V] + edge->RoadLength;
                    shortestNum[edge->AdjV] = shortestNum[V];
                    rescueNum[edge->AdjV] = rescueNum[V] + Graph->G[edge->AdjV].RescueNum;
                }
                else if (roadLength[V] + edge->RoadLength == roadLength[edge->AdjV]) {
                    shortestNum[edge->AdjV] += shortestNum[V];
                    if (rescueNum[edge->AdjV] < rescueNum[V] + Graph->G[edge->AdjV].RescueNum)
                        rescueNum[edge->AdjV] = rescueNum[V] + Graph->G[edge->AdjV].RescueNum;
                }
            }
        }
    }
    printf("%d %d\n", shortestNum[destination], rescueNum[destination]);
}
