#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define MaxVertexNum 200
#define INF 65535
/* ������������ɢ�б�HashTable���忪ʼ������������ */
#define MAXTABLESIZE 100000 /* �����ٵ����ɢ�б��� */
#define STRLENGTH 3
typedef char KeyType[STRLENGTH + 1];
typedef int ValueType;
typedef int Index;
typedef struct LNode *PtrToLNode;
struct LNode {
    KeyType Key;
    ValueType Value;
    PtrToLNode Next;
};
typedef PtrToLNode Pair;

typedef struct HNode *PtrToHNode;
struct HNode {
    PtrToLNode FirstData;
};
typedef PtrToHNode List;

typedef struct TblNode *HashTable;
struct TblNode {
    int TableSize;
    List Heads;
};
int NextPrime( int N );     // ���N�����һ������
Index Hash(const char *Key, int TableSize); // �ַ����ؼ��ֵĹ�ϣ����

HashTable CreateTable( int TableSize );
void DestroyTable( HashTable H );
Pair Find( HashTable H, KeyType Key );
bool Insert( HashTable H, KeyType Key, ValueType Value );

/* ������������ɢ�б�HashTable������������������� */
/* ����������������ͼ���ڽӱ��忪ʼ������������ */
typedef int Vertex;
typedef int WeightType;
typedef char NameType[STRLENGTH + 1];
typedef int DataType;

typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;
    WeightType cost;  // ·�ĳ���
};
typedef PtrToENode Edge;

typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode{
    Vertex AdjV;
    WeightType cost;  // ·�ĳ���
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    NameType name;
    DataType happiness;
    PtrToAdjVNode FirstEdge;
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
/* �������������Ѷ��忪ʼ������������ */
#define ERROR -1
typedef struct ItemNode *PtrToItemNode;
struct ItemNode {
    Vertex index;
    WeightType cost;
};
typedef PtrToItemNode ElementType;
int comp(PtrToItemNode a, PtrToItemNode b);

typedef struct HeapNode *Heap;
struct HeapNode {
    ElementType *Data;
    int Size;
    int Capacity;
};
typedef Heap MinHeap;

MinHeap CreateHeap(int MaxSize);
void DestoryHeap(MinHeap heap);
bool IsFull( MinHeap H );
bool IsEmpty( MinHeap H );
bool InsertNode( MinHeap H, Vertex index, WeightType cost );
Vertex DeleteMin( MinHeap H );
/* �������������Ѷ������������������ */
bool collected[MaxVertexNum];
WeightType cost[MaxVertexNum];
int routeNum[MaxVertexNum];     // ���·������
DataType happiness[MaxVertexNum];
int cityNum[MaxVertexNum];      // ���·����;���ĳ�����
Vertex path[MaxVertexNum];  // �������·������һ�����б��

void ReadInput(HashTable hTable, LGraph graph);
void init(LGraph graph);
void solve(HashTable hTable, LGraph graph);     // ʹ��Dijkstra�㷨����
void PrintAns(HashTable hTable, LGraph graph, Vertex destination);

int main()
{
    int N;
    HashTable hTable;
    LGraph graph;
    scanf("%d", &N);

    hTable = CreateTable(N);
    graph = CreateGraph(N);
    ReadInput(hTable, graph);
    solve(hTable, graph);
    DestroyTable(hTable);
    DestoryGraph(graph);
    return 0;
}

/* ������������������ݽṹ����ʵ�ֿ�ʼ������������ */
int NextPrime( int N )
{
    int i, p;

    if (N < 2) return 2;
    else p = (N % 2) ? N + 2 : N + 1;
    while( p <= MAXTABLESIZE ) {
        for( i = (int)sqrt(p); i > 1; --i )
            if ( !(p % i) ) break;
        if ( i == 1 ) break;
        else  p += 2;
    }
    return p;
}

Index Hash(const char *Key, int TableSize)
{
    unsigned int h = 0;
    while (*Key != '\0')
        h = (h << 5) + *Key++;
    return h % TableSize;
}

HashTable CreateTable( int TableSize )
{
    HashTable H;
    int i;

    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = NextPrime(TableSize);

    H->Heads = (List)malloc(H->TableSize * sizeof(struct HNode));
    for( i=0; i<H->TableSize; i++ )
        H->Heads[i].FirstData = NULL;

    return H;
}

void DestroyTable( HashTable H )
{
    int i;
    Pair P, Tmp;

    for( i = 0; i < H->TableSize; ++i ) {
        P = H->Heads[i].FirstData;
        while( P ) {
            Tmp = P->Next;
            free( P );
            P = Tmp;
        }
    }
    free( H->Heads );
    free( H );
}

Pair Find( HashTable H, KeyType Key )
{
    Pair P;
    Index Pos;

    Pos = Hash( Key, H->TableSize );
    P = H->Heads[Pos].FirstData;
    while( P && strcmp(P->Key, Key) )
        P = P->Next;

    return P;
}

bool Insert( HashTable H, KeyType Key, ValueType Value )
{
    Pair P, NewCell;
    Index Pos;

    P = Find( H, Key );
    if ( !P ) {
        NewCell = (Pair)malloc(sizeof(struct LNode));
        strcpy(NewCell->Key, Key);
        NewCell->Value = Value;
        Pos = Hash( Key, H->TableSize );
        NewCell->Next = H->Heads[Pos].FirstData;
        H->Heads[Pos].FirstData = NewCell;
        return true;
    }
    else return false;
}

LGraph CreateGraph( int VertexNum )
{
    Vertex V;
    LGraph Graph;

    Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;

    for (V = 0; V < VertexNum; ++V) {
        Graph->G[V].name[0] = '\0';
        Graph->G[V].FirstEdge = NULL;
    }

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
    NewNode->AdjV = E->V2; NewNode->cost = E->cost;
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;

    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1; NewNode->cost = E->cost;
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}

int comp(PtrToItemNode a, PtrToItemNode b)
{
    return (a->cost - b->cost);
}

MinHeap CreateHeap(int MaxSize)
{
    ElementType guard = (ElementType)malloc(sizeof(struct ItemNode));
    MinHeap H = (MinHeap)malloc(sizeof(struct HeapNode));
    guard->index = -1; guard->cost = -1;
    H->Data = (ElementType *)malloc((MaxSize + 1) * sizeof(ElementType));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Data[0] = guard;
    return H;
}

void DestoryHeap(MinHeap heap)
{
    int i;
    for (i = 0; i <= heap->Size; ++i)
        free(heap->Data[i]);
    free(heap->Data);
    free(heap);
}

bool IsFull( MinHeap H )
{
    return (H->Size == H->Capacity);
}

bool IsEmpty( MinHeap H )
{
    return (H->Size == 0);
}

bool InsertNode( MinHeap H, Vertex index, WeightType cost )
{
    int i;
    PtrToItemNode NewItem;
    if (IsFull(H)) return false;
    i = ++H->Size;
    for (; H->Data[i / 2]->cost > cost; i /= 2)
        H->Data[i] = H->Data[i / 2];
    NewItem = (PtrToItemNode)malloc(sizeof(struct ItemNode));
    NewItem->index = index; NewItem->cost = cost;
    H->Data[i] = NewItem;
    return true;
}

Vertex DeleteMin( MinHeap H )
{
    int Parent, Child;
    Vertex minV;
    ElementType X;
    if (IsEmpty(H)) return ERROR;
    minV = H->Data[1]->index;
    free(H->Data[1]);
    X = H->Data[H->Size--];
    for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
        Child = Parent * 2;
        if ((Child != H->Size) && comp(H->Data[Child], H->Data[Child + 1]) > 0)
            ++Child;
        if (comp(X, H->Data[Child]) < 0) break;
        else H->Data[Parent] = H->Data[Child];
    }
    H->Data[Parent] = X;
    return minV;
}
/* ������������������ݽṹ����ʵ�ֽ��������������� */

void ReadInput(HashTable hTable, LGraph graph)
{
    int i;
    char city1[STRLENGTH + 1], city2[STRLENGTH + 1];
    Edge edge; Pair pos1, pos2;
    scanf("%d %s", &(graph->Ne), graph->G[0].name);
    /* ��ʼ����ʼ���н�� */
    graph->G[0].happiness = 0;
    Insert(hTable, graph->G[0].name, 0);
    /* ���벢��ʼ�������н�� */
    for (i = 1; i < graph->Nv; ++i) {
        scanf("%s %d", graph->G[i].name, &(graph->G[i].happiness));
        Insert(hTable, graph->G[i].name, i);
    }
    /* �������б� */
    edge = (Edge)malloc(sizeof(struct ENode));
    for (i = 0; i < graph->Ne; ++i) {
        scanf("%s %s %d", city1, city2, &(edge->cost));
        pos1 = Find(hTable, city1); pos2 = Find(hTable, city2);
        if (!pos1 || !pos2) continue;
        edge->V1 = pos1->Value; edge->V2 = pos2->Value;
        InsertEdge(graph, edge);
    }
    free(edge);
}

void init(LGraph graph)
{
    Vertex V;
    for (V = 0; V < graph->Nv; ++V) {
        collected[V] = false;
        cost[V] = INF;
        routeNum[V] = 0;
        happiness[V] = graph->G[V].happiness;
        cityNum[V] = 0;
        path[V] = -1;
    }
}

void solve(HashTable hTable, LGraph graph)
{
    PtrToAdjVNode edge;
    MinHeap heap;
    Vertex V, destination;

    init(graph);
    heap = CreateHeap(graph->Nv * graph->Nv);
    // �Ƚ�Դ�������ȡԪ�صļ����У�Ȼ��������ڽӵ����ֵ
    collected[0] = true; cost[0] = 0; routeNum[0] = 1;
    for (edge = graph->G[0].FirstEdge; edge; edge = edge->Next) {
        if (edge->cost < cost[edge->AdjV]) {    // ��ֹ�������м��ж�����
            cost[edge->AdjV] = edge->cost;
            routeNum[edge->AdjV] += routeNum[0];
            ++cityNum[edge->AdjV];
            path[edge->AdjV] = 0;
            InsertNode(heap, edge->AdjV, edge->cost);
        }
    }
    // Ȼ�����δ�δȡԪ�����Ҿ�����С��Ԫ�ط��뼯���У����������ڽӵ����ֵ
    destination = Find(hTable, "ROM")->Value;   // �ҵ�ROM��Ӧ�ı��
    while (true) {
        V = DeleteMin(heap);
        if (V == ERROR || V == destination) break;
        if (collected[V]) continue;
        collected[V] = true;
        for (edge = graph->G[V].FirstEdge; edge; edge= edge->Next) {
            if (collected[edge->AdjV]) continue;
            if (cost[V] + edge->cost < cost[edge->AdjV]) {  // ����С��cost
                cost[edge->AdjV] = cost[V] + edge->cost;
                routeNum[edge->AdjV] = routeNum[V];
                happiness[edge->AdjV] = happiness[V] + graph->G[edge->AdjV].happiness;
                cityNum[edge->AdjV] = cityNum[V] + 1;
                path[edge->AdjV] = V;
                InsertNode(heap, edge->AdjV, cost[edge->AdjV]);
            }
            else if (cost[V] + edge->cost == cost[edge->AdjV]) {    // cost��ͬ
                routeNum[edge->AdjV] += routeNum[V];
                if (happiness[V] + graph->G[edge->AdjV].happiness > happiness[edge->AdjV]) { // �����happiness
                    happiness[edge->AdjV] = happiness[V] + graph->G[edge->AdjV].happiness;
                    cityNum[edge->AdjV] = cityNum[V] + 1;
                    path[edge->AdjV] = V;
                }
                else if (happiness[V] + graph->G[edge->AdjV].happiness == happiness[edge->AdjV]) {  // happiness��ͬ
                    if (cityNum[V] + 1 < cityNum[edge->AdjV]) {  // ����� average happiness
                        cityNum[edge->AdjV] = cityNum[V] + 1;
                        path[edge->AdjV] = V;
                    }
                }
            }
        }
    }
    DestoryHeap(heap);
    PrintAns(hTable, graph, destination);
}

void PrintAns(HashTable hTable, LGraph graph, Vertex destination)
{
    int n, i;
    Vertex V, arr[MaxVertexNum];
    V = path[destination];
    for (n = 0; V != -1; V = path[V]) {
        arr[n++] = V;
    }
    printf("%d %d %d %d\n", routeNum[destination], cost[destination], happiness[destination], happiness[destination] / cityNum[destination]);
    for (i = n - 1; i >= 0; --i)
        printf("%s->", graph->G[arr[i]].name);
    printf("ROM\n");
}
