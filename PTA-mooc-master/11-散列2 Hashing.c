#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXTABLESIZE 100000 /* �����ٵ����ɢ�б��� */
typedef int ElementType;    /* �ؼ������������� */
typedef int Index;          /* ɢ�е�ַ���� */
typedef Index Position;     /* ��������λ����ɢ�е�ַ��ͬһ���� */
/* ɢ�е�Ԫ״̬���ͣ��ֱ��Ӧ���кϷ�Ԫ�ء��յ�Ԫ������ɾ��Ԫ�� */
typedef enum { Legitimate, Empty } EntryType;

typedef struct HashEntry Cell; /* ɢ�б�Ԫ���� */
struct HashEntry{
    ElementType Data; /* ���Ԫ�� */
    EntryType Info;   /* ��Ԫ״̬ */
};

typedef struct TblNode *HashTable; /* ɢ�б����� */
struct TblNode {   /* ɢ�б��㶨�� */
    int TableSize; /* �����󳤶� */
    Cell *Cells;   /* ���ɢ�е�Ԫ���ݵ����� */
};

int NextPrime(int N);   // ���ش���N�Ҳ�����MAXTABLESIZE����С����
HashTable CreateTable( int TableSize );
void DestoryTable(HashTable H);
int Hash(int Key, int p);

Position Find( HashTable H, ElementType Key );
Position Insert( HashTable H, ElementType Key );

int main()
{
    int TableSize, N, i, tmp;
    Position pos;
    HashTable H;

    scanf("%d %d", &TableSize, &N);
    H = CreateTable(TableSize);
    for (i = 0; i < N; ++i) {
        scanf("%d", &tmp);
        pos = Insert(H, tmp);
        if (i != 0) printf(" ");
        if (pos == -1)
            printf("-");
        else
            printf("%d", pos);
    }
    DestoryTable(H);

    return 0;
}

int NextPrime( int N )
{
    int i, p;

    if (N < 2) return 2;
    else p = (N%2)? N+2 : N+1; /*�Ӵ���N����һ��������ʼ */
    while( p <= MAXTABLESIZE ) {
        for( i=(int)sqrt(p); i>1; i-- )
            if ( !(p%i) ) break; /* p�������� */
        if ( i==1 ) break; /* for����������˵��p������ */
        else  p += 2; /* ������̽��һ������ */
    }
    return p;
}

HashTable CreateTable( int TableSize )
{
    HashTable H;
    int i;

    H = (HashTable)malloc(sizeof(struct TblNode));
    /* ��֤ɢ�б���󳤶������� */
    H->TableSize = NextPrime(TableSize);
    /* ������Ԫ���� */
    H->Cells = (Cell *)malloc(H->TableSize*sizeof(Cell));
    /* ��ʼ����Ԫ״̬Ϊ���յ�Ԫ�� */
    for( i=0; i<H->TableSize; i++ )
        H->Cells[i].Info = Empty;

    return H;
}

void DestoryTable(HashTable H)
{
    if (!H)
        free(H->Cells);
    free(H);
}

int Hash(int Key, int P)
{
    return Key % P;
}

Position Find( HashTable H, ElementType Key )
{
    Position CurrentPos, NewPos;
    int CNum = 0; /* ��¼��ͻ���� */

    NewPos = CurrentPos = Hash( Key, H->TableSize ); /* ��ʼɢ��λ�� */
    /* ����λ�õĵ�Ԫ�ǿգ����Ҳ���Ҫ�ҵ�Ԫ��ʱ��������ͻ */
    while( H->Cells[NewPos].Info!=Empty && H->Cells[NewPos].Data!=Key ) {
                                           /* �ַ������͵Ĺؼ�����Ҫ strcmp ����!! */
        NewPos = CurrentPos + (CNum+1)*(CNum+1);
        if ( NewPos >= H->TableSize ) {
            NewPos = NewPos % H->TableSize; /* ����Ϊ�Ϸ���ַ */
            if (NewPos == CurrentPos)
                break;
        }
        ++CNum;
    }
    return NewPos; /* ��ʱNewPos������Key��λ�ã�������һ���յ�Ԫ��λ�ã���ʾ�Ҳ�����*/
}

Position Insert( HashTable H, ElementType Key )
{
    Position Pos = Find( H, Key ); /* �ȼ��Key�Ƿ��Ѿ����� */

    if( H->Cells[Pos].Info != Legitimate ) { /* ��������Ԫû�б�ռ��˵��Key���Բ����ڴ� */
        H->Cells[Pos].Info = Legitimate;
        H->Cells[Pos].Data = Key;
        return Pos;
    }
    else
        return -1;
}
