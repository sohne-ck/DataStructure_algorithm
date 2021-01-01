#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 1000
#define INF 65535
typedef int Vertex;
typedef int WeightType;

typedef struct ENode *PtrToENode;
struct ENode {
    Vertex V1, V2;
    WeightType weight;
};
typedef PtrToENode Edge;
/*-------------------- ���㲢�鼯���� --------------------*/
typedef Vertex SetName;     /* Ĭ���ø������±���Ϊ�������� */
typedef Vertex SetType[MaxVertexNum]; /* ���輯��Ԫ���±��0��ʼ */

void InitializeVSet( SetType S, int N )
{ /* ��ʼ�����鼯 */
    Vertex X;

    for ( X=0; X<N; X++ ) S[X] = -1;
}

void Union( SetType S, SetName Root1, SetName Root2 )
{ /* ����Ĭ��Root1��Root2�ǲ�ͬ���ϵĸ���� */
    /* ��֤С���ϲ���󼯺� */
    if ( S[Root2] < S[Root1] ) { /* �������2�Ƚϴ� */
        S[Root2] += S[Root1];     /* ����1���뼯��2  */
        S[Root1] = Root2;
    }
    else {                         /* �������1�Ƚϴ� */
        S[Root1] += S[Root2];     /* ����2���뼯��1  */
        S[Root2] = Root1;
    }
}

SetName Find( SetType S, Vertex X )
{ /* Ĭ�ϼ���Ԫ��ȫ����ʼ��Ϊ-1 */
    if ( S[X] < 0 ) /* �ҵ����ϵĸ� */
        return X;
    else
        return S[X] = Find( S, S[X] ); /* ·��ѹ�� */
}

int CheckCycle( SetType VSet, Vertex V1, Vertex V2 )
{ /* �������V1��V2�ı��Ƿ������е���С�������Ӽ��й��ɻ�· */
    Vertex Root1, Root2;

    Root1 = Find( VSet, V1 ); /* �õ�V1��������ͨ������ */
    Root2 = Find( VSet, V2 ); /* �õ�V2��������ͨ������ */

    if( Root1==Root2 ) /* ��V1��V2�Ѿ���ͨ����ñ߲���Ҫ */
        return 0;
    else { /* ����ñ߿��Ա��ռ���ͬʱ��V1��V2����ͬһ��ͨ�� */
        Union( VSet, Root1, Root2 );
        return 1;
    }
}
/*-------------------- ���鼯������� --------------------*/
int vertexNum, edgeNum;
struct ENode edges[MaxVertexNum * 3];

int comp(const void *a, const void *b)
{
    return (*(Edge)a).weight - (*(Edge)b).weight;
}

void initEdges();
int Kruskal();

int main()
{
    printf("%d", Kruskal());

    return 0;
}

void initEdges()
{
    int i;
    scanf("%d %d", &vertexNum, &edgeNum);
    for (i = 0; i < edgeNum; ++i) {
        scanf("%d %d %d", &(edges[i].V1), &(edges[i].V2), &(edges[i].weight));
        --edges[i].V1;  --edges[i].V2;
    }

    qsort(edges, edgeNum, sizeof(struct ENode), comp);
}

int Kruskal()
{
    SetType VSet;
    struct ENode nextEdge;
    int ECount, i; WeightType totalweight;

    initEdges();
    InitializeVSet(VSet, vertexNum);

    ECount = 0; totalweight = 0; i = 0;
    while (ECount < vertexNum - 1) {
        if (i < edgeNum)
            nextEdge = edges[i++];
        else
            break;
        if (CheckCycle(VSet, nextEdge.V1, nextEdge.V2)) {
            totalweight += nextEdge.weight;
            ++ECount;
        }
    }
    if (ECount < vertexNum - 1)
        totalweight = -1;

    return totalweight;
}
