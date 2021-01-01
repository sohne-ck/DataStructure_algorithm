#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* ������������ͼ���ڽӱ��ʾ��ض��忪ʼ������������ */
#define MaxVertexNum 1000    /* ��󶥵�����Ϊ100 */
typedef int Index;         /* �ö����±��ʾ����,Ϊ���� */
typedef int ElementType;

/* �ߵĶ��� */
typedef struct ENode *PtrToENode;
struct ENode{
    Index V1, V2;      /* �����<V1, V2> */
};
typedef PtrToENode Edge;

/* �ڽӵ�Ķ��� */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
    Index AdjV;        /* �ڽӵ��±� */
    PtrToAdjVNode Next;    /* ָ����һ���ڽӵ��ָ�� */
};

/* �����ͷ���Ķ��� */
typedef struct Vnode{
    ElementType data;   // �ö������ֵ��-1��ʾ�ö��㲻����
    int indegree;   // �ö������ȣ�������ʱΪ-1
    PtrToAdjVNode FirstEdge;/* �߱�ͷָ�� */
} AdjList[MaxVertexNum];    /* AdjList���ڽӱ����� */

/* ͼ���Ķ��� */
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;     /* ������ */
    AdjList G;  /* �ڽӱ� */
};
typedef PtrToGNode LGraph; /* ���ڽӱ�ʽ�洢��ͼ���� */

LGraph CreateGraph( int VertexNum );    // ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ
void DestoryGraph( LGraph Graph );
void InsertEdge( LGraph Graph, Edge E );
/* ������������ͼ���ڽӱ��ʾ��ض������������������ */
/* �������������ѵ���ض��忪ʼ������������ */
typedef struct HNode *Heap; /* �ѵ����Ͷ��� */
struct HNode {
    Index *Data; /* �洢Ԫ�ص����飬Data[0]�洢Ԫ�ظ��� */
    int Capacity;      /* �ѵ�������� */
};
typedef Heap MinHeap; /* ��С�� */

#define ERROR -1 /* �����ʶӦ���ݾ����������Ϊ���в����ܳ��ֵ�Ԫ��ֵ */
MinHeap CreateHeap( int MaxSize );
void DestoryHeap(MinHeap heap);
bool IsFull( MinHeap H );
bool IsEmpty( MinHeap H );
bool Insert( LGraph graph, MinHeap H, Index X );    // ��Ԫ��X������С��H
Index DeleteMin( LGraph graph, MinHeap H ); // ����С��H��ȡ����ֵ��С��Ԫ�أ���ɾ��һ�����
/* �������������ѵ���ض������������������ */

LGraph buildGraph();
void handleAndPrint(LGraph graph);

int main()
{
    LGraph graph;
    graph = buildGraph();
    handleAndPrint(graph);
    DestoryGraph(graph);

    return 0;
}

LGraph CreateGraph( int VertexNum )
{ /* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
    Index V;
    LGraph Graph;

    Graph = (LGraph)malloc( sizeof(struct GNode) ); /* ����ͼ */
    Graph->Nv = VertexNum;
    /* ��ʼ���ڽӱ�ͷָ�� */
    /* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
    for (V=0; V<Graph->Nv; V++) {
        Graph->G[V].data = -1;
        Graph->G[V].indegree = -1;
        Graph->G[V].FirstEdge = NULL;
    }

    return Graph;
}

void DestoryGraph( LGraph Graph )
{
    Index V;
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

void InsertEdge( LGraph Graph, Edge E )
{
    PtrToAdjVNode NewNode;

    /* ����� <V1, V2> */
    /* ΪV2�����µ��ڽӵ� */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    /* ��V2����V1�ı�ͷ */
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
}

MinHeap CreateHeap( int MaxSize )
{
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType *)malloc((MaxSize+1)*sizeof(ElementType));
    H->Data[0] = 0;
    H->Capacity = MaxSize;

    return H;
}

void DestoryHeap(MinHeap heap)
{
    free(heap->Data);
    free(heap);
}

bool IsFull( MinHeap H )
{
    return (H->Data[0] == H->Capacity);
}

bool Insert( LGraph graph, MinHeap H, Index X )
{
    int i;

    if ( IsFull(H) ) return false;
    i = ++(H->Data[0]); /* iָ��������е����һ��Ԫ�ص�λ�� */
    for ( ; (i / 2 > 0) && graph->G[H->Data[i/2]].data > graph->G[X].data; i/=2 )
        H->Data[i] = H->Data[i/2]; /* ����X */
    H->Data[i] = X; /* ��X���� */
    return true;
}

bool IsEmpty( MinHeap H )
{
    return (H->Data[0] == 0);
}

Index DeleteMin( LGraph graph, MinHeap H )
{
    int Parent, Child;
    Index MinItem, X;

    if ( IsEmpty(H) ) return ERROR;

    MinItem = H->Data[1]; /* ȡ��������ŵ���Сֵ */
    /* ����С�������һ��Ԫ�شӸ���㿪ʼ���Ϲ����²��� */
    X = H->Data[H->Data[0]--]; /* ע�⵱ǰ�ѵĹ�ģҪ��С */
    for( Parent=1; Parent*2<=H->Data[0]; Parent=Child ) {
        Child = Parent * 2;
        if( (Child!=H->Data[0]) && (graph->G[H->Data[Child]].data > graph->G[H->Data[Child+1]].data) )
            Child++;  /* Childָ�������ӽ��Ľ�С�� */
        if( graph->G[X].data <= graph->G[H->Data[Child]].data ) break; /* �ҵ��˺���λ�� */
        else  /* ����X */
            H->Data[Parent] = H->Data[Child];
    }
    H->Data[Parent] = X;

    return MinItem;
}

LGraph buildGraph()
{
    int n;
    Index i, j;
    Edge e;
    LGraph graph;

    e = (Edge)malloc(sizeof(struct ENode));
    scanf("%d", &n);
    graph = CreateGraph(n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &(graph->G[i].data));
        if (graph->G[i].data < 0) continue;   // û�д���ֵ�������ô�
        j = graph->G[i].data % graph->Nv;
        graph->G[i].indegree = (i - j + graph->Nv) % graph->Nv;
        while (j != i) {
            e->V1 = j; e->V2 = i;
            InsertEdge(graph, e);
            j = (j + 1) % graph->Nv;
        }
    }
    free(e);
    return graph;
}

void handleAndPrint(LGraph graph)
{
    MinHeap heap;
    Index i, pos;
    PtrToAdjVNode tmp;
    bool isFirst;
    heap = CreateHeap(graph->Nv);
    isFirst = true;
    for (i = 0; i < graph->Nv; ++i) {   // �����Ϊ0�Ľ��������
        if (graph->G[i].indegree == 0)
            Insert(graph, heap, i);
    }
    while (!IsEmpty(heap)) {    // ������������ʹ�öѣ������ȶ��У�������һ�����
        pos = DeleteMin(graph, heap);
        tmp = graph->G[pos].FirstEdge;
        while (tmp) {
           if (--(graph->G[tmp->AdjV].indegree) == 0)
                Insert(graph, heap, tmp->AdjV);
           tmp = tmp->Next;
        }
        if (isFirst) isFirst = false;
        else printf(" ");
        printf("%d", graph->G[pos].data);
    }
    DestoryHeap(heap);
}
