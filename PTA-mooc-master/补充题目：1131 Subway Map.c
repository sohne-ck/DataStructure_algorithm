#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 65535
/* ����������������ͼ���ڽӱ��忪ʼ������������ */
#define MaxVertexNum 10000
typedef int Vertex;

typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;
    int lineNo;     // �������ڼ�������
};
typedef PtrToENode Edge;

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
    Vertex AdjV;
    int lineNo;     // �������ڼ�������
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph BuildGraph();
void DestoryGraph( LGraph Graph );
void InsertEdge(LGraph Graph, Edge E);
/* ����������������ͼ���ڽӱ������������������ */
/* ���������������ж��忪ʼ������������ */
#define ERROR -1
typedef int ElementType;
typedef int Position;
struct QNode {
    ElementType *Data;     /* �洢Ԫ�ص����� */
    Position Front, Rear;  /* ���е�ͷ��βָ�� */
    int MaxSize;
};
typedef struct QNode *Queue;

Queue CreateQueue(int MaxSize);
void DestoryQueue( Queue Q );
bool IsFull( Queue Q );
bool Enqueue( Queue Q, ElementType X );
bool IsEmpty( Queue Q );
ElementType Dequeue( Queue Q );
void Clear(Queue Q);
/* ���������������ж������������������ */
int dist[MaxVertexNum]; // ·������
Vertex path[MaxVertexNum];  // ��һ��վ����
int transferNum[MaxVertexNum];  // ���˴���
int curLine[MaxVertexNum];  // ��ǰ���ڵ����ߣ����Ŷ�ȡ�ı߶��ı�

void reset();    // ���踨������ĳ�ʼֵ
void printRoute(Vertex source);
void query(LGraph graph, Queue queue);

int main()
{
    LGraph graph;
    Queue queue;
    int queryNum, i;
    graph = BuildGraph();
    queue = CreateQueue(MaxVertexNum + 1);
    scanf("%d", &queryNum);
    for (i = 0; i < queryNum; ++i)
        query(graph, queue);
    DestoryGraph(graph);
    DestoryQueue(queue);

    return 0;
}

/* ������������������ݽṹ����ʵ�ֿ�ʼ������������ */
LGraph BuildGraph()
{
    LGraph graph; Edge edge;
    int lineNum, stopNum, i, j;
    Vertex preStop, curStop, V;

    graph = (LGraph)malloc(sizeof(struct GNode));
    for (V = 0; V < MaxVertexNum; ++V) graph->G[V].FirstEdge = NULL;
    edge = (Edge)malloc(sizeof(struct ENode));
    scanf("%d", &lineNum);
    for (i = 1; i <= lineNum; ++i) {
        preStop = -1;
        scanf("%d", &stopNum);
        for (j = 0; j < stopNum; ++j) {
            scanf("%d", &curStop);
            if (preStop != -1) {
                edge->V1 = preStop; edge->V2 = curStop; edge->lineNo = i;
                InsertEdge(graph, edge);
            }
            preStop = curStop;
        }
    }
    free(edge);

    return graph;
}

void DestoryGraph( LGraph Graph )
{
    Vertex V;
    PtrToAdjVNode Node;
    if (!Graph) return;
    for (V = 0; V < MaxVertexNum; ++V) {
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
    NewNode->AdjV = E->V2; NewNode->lineNo = E->lineNo;
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;

    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1; NewNode->lineNo = E->lineNo;
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}

Queue CreateQueue(int MaxSize)
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (int *)malloc(MaxSize * sizeof(int));
    Q->Front = Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}

void DestoryQueue( Queue Q )
{
    if (Q) {
        if (Q->Data)
            free(Q->Data);
        free(Q);
    }
}

bool IsFull( Queue Q )
{
    return ((Q->Rear+1)%Q->MaxSize == Q->Front);
}

bool Enqueue( Queue Q, ElementType X )
{
    if ( IsFull(Q) ) return false;
    else {
        Q->Rear = (Q->Rear+1)%Q->MaxSize;
        Q->Data[Q->Rear] = X;
        return true;
    }
}

bool IsEmpty( Queue Q )
{
    return (Q->Front == Q->Rear);
}

ElementType Dequeue( Queue Q )
{
    if ( IsEmpty(Q) ) return ERROR;
    else  {
        Q->Front =(Q->Front+1)%Q->MaxSize;
        return  Q->Data[Q->Front];
    }
}

void Clear(Queue Q)
{
    Q->Front = Q->Rear = 0;
}
/* ������������������ݽṹ����ʵ�ֽ��������������� */

void reset()
{
    Vertex V;
    for (V = 0; V < MaxVertexNum; ++V) {
        dist[V] = 0;
        path[V] = -1;
        transferNum[V] = -1;
        curLine[V] = 0;
    }
}

void printRoute(Vertex source)
{
    Vertex transfer;
    printf("%d\n", dist[source]);
    while (transferNum[source] >= 0) {
        for (transfer = path[source]; transfer != -1 && curLine[source] == curLine[transfer]; transfer = path[transfer]) ;  // �ҵ�����վ
        printf("Take Line#%d from %04d to %04d.\n", curLine[source], source, transfer);
        source = transfer;
    }
}

void query(LGraph graph, Queue queue)
{
    Vertex source, destination, V;
    int tmpTransfreNum;
    PtrToAdjVNode edge;

    scanf("%d %d", &source, &destination);
    reset();
    Clear(queue);
    Enqueue(queue, destination);
    while(!IsEmpty(queue)) {
        V = Dequeue(queue);
        if (V == source) break;
        for (edge = graph->G[V].FirstEdge; edge; edge = edge->Next) {
            if (dist[edge->AdjV] == 0 && edge->AdjV != destination) {    // ���û���ʹ�
                dist[edge->AdjV] = dist[V] + 1;
                path[edge->AdjV] = V;
                curLine[edge->AdjV] = edge->lineNo;
                transferNum[edge->AdjV] = (curLine[V] != edge->lineNo) ? transferNum[V] + 1 : transferNum[V];
                Enqueue(queue, edge->AdjV);
            }
            else if (dist[V] + 1 == dist[edge->AdjV]) { // ������ʹ���������һ����
                tmpTransfreNum = (edge->lineNo == curLine[V]) ? transferNum[V] : (transferNum[V] + 1);
                if (tmpTransfreNum < transferNum[edge->AdjV]) {
                    path[edge->AdjV] = V;
                    transferNum[edge->AdjV] = tmpTransfreNum;
                    curLine[edge->AdjV] = edge->lineNo;
                }
            }
        }
    }
    printRoute(source);
}
