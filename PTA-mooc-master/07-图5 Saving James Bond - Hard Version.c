#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* ���ж��忪ʼ */
#define MaxSize 101
#define ERROR -1
typedef int Position;
struct QNode {
    int *Data;     /* �洢Ԫ�ص����� */
    Position Front, Rear;  /* ���е�ͷ��βָ�� */
};
typedef struct QNode *Queue;

Queue CreateQueue()
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (int *)malloc(MaxSize * sizeof(int));
    Q->Front = Q->Rear = 0;
    return Q;
}

void DestoryQueue( Queue Q )
{
    if (Q->Data) free(Q->Data);
    free(Q);
}

int IsFull( Queue Q )
{
    return ((Q->Rear+1)%MaxSize == Q->Front);
}

void Enqueue( Queue Q, int X )
{
    if ( IsFull(Q) ) return;
    else {
        Q->Rear = (Q->Rear+1)%MaxSize;
        Q->Data[Q->Rear] = X;
    }
}

int IsEmpty( Queue Q )
{
    return (Q->Front == Q->Rear);
}

int Dequeue( Queue Q )
{
    if ( IsEmpty(Q) ) return ERROR;
    else  {
        Q->Front =(Q->Front+1)%MaxSize;
        return  Q->Data[Q->Front];
    }
}
/* ���ж������ */

#define MaxVertexNum 100
#define INF 65535
#define ISLAND_DIAMETER 15/2.0
typedef struct Position Point;
struct Position {
    int x;
    int y;
};
Point points[MaxVertexNum];
int dist[MaxVertexNum];    // ·������
int path[MaxVertexNum];  // ��һ�����

void ReadPoints(int num);

int Distance(Point p1, Point p2);   //����������
int Jump(Point p1, Point p2, int dis);  // �ж��ܷ���Ծ��ȥ
int isSafe(Point p, int dis);   // �Ƿ������ϰ�
void PrintPath(int ans);
void Save007(int num, int dis); // ��ʵ����һ��BFS����

int main()
{
    int num, dis;
    scanf("%d %d", &num, &dis);

    ReadPoints(num);
    Save007(num, dis);

    return 0;
}

void ReadPoints(int num)
{
    int i;
    for (i = 0; i < num; ++i) {
        scanf("%d %d", &(points[i].x), &(points[i].y));
    }
}

int Distance(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

int Jump(Point p1, Point p2, int dis)
{
    return Distance(p1, p2) <= dis * dis;
}

int isSafe(Point p, int dis)
{
    return ((abs(p.x) + dis) >= 50 || (abs(p.y) + dis) >= 50);
}

void PrintPath(int ans)
{
    printf("%d\n", dist[ans] + 1);
    for (; ans != -1; ans = path[ans]) {
        printf("%d %d\n", points[ans].x, points[ans].y);
    }
}

void Save007(int num, int dis)
{
    int i, cur_dis, pIndex, ans;
    Queue Q;
    Point center;
    center.x = 0; center.y = 0;

    if (isSafe(center, dis + ISLAND_DIAMETER)) {    // ����ӵ��Ͼ���ֱ�����ϰ�
        printf("1\n");
        return;
    }

    for (i = 0; i < num; ++i) {     // ��ʼ����������
        dist[i] = INF;
        path[i] = -1;
    }
    Q = CreateQueue();
    for (i = 0; i < num; ++i) {
        if (isSafe(points[i], dis)) {   // ���������ϰ������
            dist[i] = 1;
            Enqueue(Q, i);
        }
    }
    cur_dis = 1; ans = -1;
    while (!IsEmpty(Q)) {
        pIndex = Dequeue(Q);
        if (dist[pIndex] == cur_dis + 1 && ans != -1) break;  // �Ѿ������굱ǰ��
        if (Jump(center, points[pIndex], dis + ISLAND_DIAMETER)) {
            if (ans == -1 || Distance(center, points[pIndex]) < Distance(center, points[ans]))
                ans = pIndex;
        }
        else {
            for (i = 0; i < num; ++i) {
                if (Jump(points[pIndex], points[i], dis) && (dist[pIndex] + 1 < dist[i])) {
                    dist[i] = dist[pIndex] + 1;
                    path[i] = pIndex;
                    Enqueue(Q, i);
                }
            }
        }
        cur_dis = dist[pIndex];
    }
    if (ans == -1) printf("0\n");
    else PrintPath(ans);
    DestoryQueue(Q);
}
