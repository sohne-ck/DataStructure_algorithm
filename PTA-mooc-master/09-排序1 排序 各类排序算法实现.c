#include <stdio.h>
#include <stdlib.h>

#define QuickSort_Cutoff 50 // ����������С���򳤶ȣ����������г���С�ڸ���ֵʱ��ʹ�ò�������

// ����Ԫ�������4λ
#define MaxDigit 4
#define Radix 10

typedef int ElementType;

/* ������������Ͱ�����������ݽṹ���忪ʼ������������ */
/* ͰԪ�ؽ�� */
typedef struct Node *PtrToNode;
struct Node {
    int key;
    PtrToNode next;
};

/* Ͱͷ��� */
struct HeadNode {
    PtrToNode head, tail;
};
typedef struct HeadNode Bucket[Radix];
/* ������������Ͱ�����������ݽṹ������������������� */

void Swap (ElementType *a, ElementType *b)
{
    ElementType t = *a; *a = *b; *b = t;
}

ElementType *ReadInput(int N);
void PrintArr(ElementType A[], int N);

void PercDown(ElementType A[], int p, int N);   // ������ʹ�ú���
void Merge_Recursive(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd);  // �ݹ�Ĺ鲢����ʹ�ú���
void Merge_NotRecursive(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd);   // �ǵݹ�Ĺ鲢����ʹ�ú���
void Msort(ElementType A[], ElementType TmpA[], int L, int RightEnd);   // �ݹ�Ĺ鲢����ʹ�ú���
void Merge_pass(ElementType A[], ElementType TmpA[], int N, int length);    // �ǵݹ�Ĺ鲢����ʹ�ú���
ElementType Median3( ElementType A[], int Left, int Right );    // ���������е�ѡ��Ԫ�������˴�ʹ������ȡ�з�
void Qsort(ElementType A[], int Left, int Right);   // ��������ĵݹ麯��
int GetDigit(int X, int D);     // �������������ڻ�ȡ��Ӧλ�����ֵĺ���
void MSD(ElementType A[], int L, int R, int D);     // ��λ���ȵĻ�������ĺ��ĵݹ麯��

// �������㷨ʵ�ֽӿڼ���Ӧ��ƽ��ʱ�临�Ӷ�˵��
void Selection_Sort(ElementType A[], int N);    // ��ѡ������O(n^2)
void Bubble_Sort(ElementType A[], int N);   // ð������O(n^2)������������Ϊ��ʱ�����Ե�4��6��8��ʱ������
void Insertion_Sort(ElementType A[], int N);    // ��������O(n^2)
void Shell_Sort(ElementType A[], int N);    // ϣ������O(n^(1.3��2))
void Heap_Sort(ElementType A[], int N);     // ������O(n*logn)
void Merge_Sort_Recursive(ElementType A[], int N);  // �ݹ�Ĺ鲢����O(n*logn)
void Merge_Sort_NotRecursive(ElementType A[], int N);  // �ǵݹ�Ĺ鲢����O(n*logn)
void Quick_Sort(ElementType A[], int N);    // ��������O(n*logn)
// ����������ܴ�������ֵ��������ݣ����ֻ�����Ե�8�Ľ������
void LSD_Radix_Sort(ElementType A[], int N);    // ��λ���ȵĻ�������O(P*(N+B))��PΪ������BΪͰ����
void MSD_Radix_Sort(ElementType A[], int N);    // ��λ���ȵĻ�������

int main()
{
    int N;
    ElementType *arr;
    scanf("%d", &N);
    arr = ReadInput(N);
    LSD_Radix_Sort(arr, N);
    PrintArr(arr, N);
    free(arr);

    return 0;
}

ElementType *ReadInput(int N)
{
    ElementType *arr;
    int i;
    arr = (ElementType *)malloc(sizeof(ElementType) * N);
    for (i = 0 ; i < N; ++i)
        scanf("%d", &arr[i]);
    return arr;
}

void PrintArr(ElementType A[], int N)
{
    int i;
    for ( i = 0; i < N - 1; ++i)
        printf("%d ", A[i]);
    printf("%d", A[i]);
}

void PercDown(ElementType A[], int p, int N)
{
    int Parent, Child;
    ElementType X;

    X = A[p];
    for (Parent = p; (Parent * 2 + 1) < N; Parent = Child) {
        Child = Parent * 2 + 1;
        if ((Child != N - 1) && (A[Child] < A[Child + 1]))
            ++Child;
        if (X >= A[Child]) break;
        else
            A[Parent] = A[Child];
    }
    A[Parent] = X;
}

void Merge_Recursive(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd)
{
    int LeftEnd, NumElements, Tmp;
    int i;

    LeftEnd = R - 1;
    Tmp = L;
    NumElements = RightEnd - L + 1;

    while (L <= LeftEnd && R <= RightEnd) {
        if (A[L] < A[R])
            TmpA[Tmp++] = A[L++];
        else
            TmpA[Tmp++] = A[R++];
    }
    while (L <= LeftEnd) TmpA[Tmp++] = A[L++];
    while (R <= RightEnd) TmpA[Tmp++] = A[R++];

    for (i = 0; i < NumElements; ++i, --RightEnd)
        A[RightEnd] = TmpA[RightEnd];
}

void Merge_NotRecursive(ElementType A[], ElementType TmpA[], int L, int R, int RightEnd)
{
    int LeftEnd, Tmp;

    LeftEnd = R - 1;
    Tmp = L;

    while (L <= LeftEnd && R <= RightEnd) {
        if (A[L] < A[R])
            TmpA[Tmp++] = A[L++];
        else
            TmpA[Tmp++] = A[R++];
    }
    while (L <= LeftEnd) TmpA[Tmp++] = A[L++];
    while (R <= RightEnd) TmpA[Tmp++] = A[R++];
}

void Msort(ElementType A[], ElementType TmpA[], int L, int RightEnd)
{
    int Center;

    if (L < RightEnd) {
        Center = (L + RightEnd) / 2;
        Msort(A, TmpA, L, Center);
        Msort(A, TmpA, Center + 1, RightEnd);
        Merge_Recursive(A, TmpA, L, Center + 1, RightEnd);
    }
}

void Merge_pass(ElementType A[], ElementType TmpA[], int N, int length)
{
    int i, j;

    for (i = 0; i <= N - 2 * length; i += 2 * length)
        Merge_NotRecursive(A, TmpA, i, i + length, i + 2 * length - 1);
    if (i + length < N)
        Merge_NotRecursive(A, TmpA, i, i + length, N - 1);
    else
        for (j = i; j < N; ++j) TmpA[j] = A[j];
}

ElementType Median3( ElementType A[], int Left, int Right )
{
    int Center = (Left+Right) / 2;
    if ( A[Left] > A[Center] )
        Swap( &A[Left], &A[Center] );
    if ( A[Left] > A[Right] )
        Swap( &A[Left], &A[Right] );
    if ( A[Center] > A[Right] )
        Swap( &A[Center], &A[Right] );
    Swap( &A[Center], &A[Right-1] );
    return  A[Right-1];
}

void Qsort(ElementType A[], int Left, int Right)
{
    int Pivot, Low, High;

    if (QuickSort_Cutoff <= Right - Left) {
        Pivot = Median3(A, Left, Right);
        Low = Left; High = Right - 1;
        while (1) {
            while(A[++Low] < Pivot) ;
            while(A[--High] > Pivot) ;
            if (Low < High) Swap(&A[Low], &A[High]);
            else break;
        }
        Swap(&A[Low], &A[Right - 1]);
        Qsort(A, Left, Low - 1);
        Qsort(A, Low + 1, Right);
    }
    else Insertion_Sort(A + Left, Right - Left + 1);
}

int GetDigit ( int X, int D )
{ /* Ĭ�ϴ�λD=1, ��λD<=MaxDigit */
    int d, i;

    for (i = 1; i <= D; ++i) {
        d = X % Radix;
        X /= Radix;
    }
    return d;
}

void MSD( ElementType A[], int L, int R, int D )
{ /* ���ĵݹ麯��: ��A[L]...A[R]�ĵ�Dλ���������� */
     int Di, i, j;
     Bucket B;
     PtrToNode tmp, p, List = NULL;
     if (D == 0) return; /* �ݹ���ֹ���� */

     for (i = 0; i < Radix; ++i) /* ��ʼ��ÿ��ͰΪ������ */
         B[i].head = B[i].tail = NULL;
     for (i = L; i <= R; ++i) { /* ��ԭʼ������������ʼ����List */
         tmp = (PtrToNode)malloc(sizeof(struct Node));
         tmp->key = A[i];
         tmp->next = List;
         List = tmp;
     }
     /* �����Ƿ���Ĺ��� */
     p = List;
     while (p) {
         Di = GetDigit(p->key, D); /* ��õ�ǰԪ�صĵ�ǰλ���� */
         /* ��List��ժ�� */
         tmp = p; p = p->next;
         /* ����B[Di]��Ͱ */
         if (B[Di].head == NULL) B[Di].tail = tmp;
         tmp->next = B[Di].head;
         B[Di].head = tmp;
     }
     /* �������ռ��Ĺ��� */
     i = j = L; /* i, j��¼��ǰҪ�����A[]�����Ҷ��±� */
     for (Di = 0; Di < Radix; ++Di) { /* ����ÿ��Ͱ */
         if (B[Di].head) { /* ���ǿյ�Ͱ��Ͱ����A[], �ݹ����� */
             p = B[Di].head;
             while (p) {
                 tmp = p;
                 p = p->next;
                 A[j++] = tmp->key;
                 free(tmp);
             }
             /* �ݹ�Ը�Ͱ��������, λ����1 */
             MSD(A, i, j-1, D-1);
             i = j; /* Ϊ��һ��Ͱ��Ӧ��A[]��� */
         }
     }
}

void Selection_Sort(ElementType A[], int N)
{
    int i, j, min_index;

    for (i = 0; i < N; ++i) {
        min_index = i;
        for (j = i + 1; j < N; ++j)
            if (A[j] < A[min_index])
                min_index = j;
        Swap(&A[i], &A[min_index]);
    }
}

void Bubble_Sort(ElementType A[], int N)
{
    int P, i, flag;
    for (P = N - 1; P > 0; --P) {
        flag = 0;
        for (i = 0; i < P; ++i) {
            if (A[i] > A[i + 1]) {
                Swap(&A[i], &A[i + 1]);
                flag = 1;
            }
        }
        if (!flag) break;
    }
}

void Insertion_Sort(ElementType A[], int N)
{
    int i, P;
    ElementType Tmp;

    for (P = 1; P < N; ++P) {
        Tmp = A[P];
        for (i = P; i > 0 && A[i - 1] > Tmp; --i)
            A[i] = A[i - 1];
        A[i] = Tmp;
    }
}

void Shell_Sort(ElementType A[], int N)
{
    int Si, D, i, P;
    ElementType Tmp;
    int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};

    for (Si = 0; Sedgewick[Si] >= N; ++Si);

    for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si]) {
        for (P = D; P < N; ++P) {
            Tmp = A[P];
            for (i = P; i >= D && A[i - D] > Tmp; i -= D)
                A[i] = A[i - D];
            A[i] = Tmp;
        }
    }
}

void Heap_Sort(ElementType A[], int N)
{
    int i;

    for (i = N / 2 - 1; i >= 0; --i)
        PercDown(A, i, N);

    for (i = N - 1; i > 0; --i) {
        Swap(&A[0], &A[i]);
        PercDown(A, 0, i);
    }
}

void Merge_Sort_Recursive(ElementType A[], int N)
{
    ElementType *TmpA;
    TmpA = (ElementType *)malloc(N * sizeof(ElementType));

    if (TmpA != NULL) {
        Msort(A, TmpA, 0, N - 1);
        free(TmpA);
    }
}

void Merge_Sort_NotRecursive(ElementType A[], int N)
{
    int length;
    ElementType *TmpA;

    length = 1;
    TmpA = (ElementType *)malloc(N * sizeof(ElementType));
    if (TmpA != NULL) {
        while (length < N) {
            Merge_pass(A, TmpA, N, length);
            length *= 2;
            Merge_pass(TmpA, A, N, length);
            length *= 2;
        }
        free(TmpA);
    }
}

void Quick_Sort(ElementType A[], int N)
{
    Qsort(A, 0, N - 1);
}

void LSD_Radix_Sort(ElementType A[], int N)
{
     int D, Di, i;
     Bucket B;
     PtrToNode tmp, p, List = NULL;

     for (i = 0; i < Radix; ++i) /* ��ʼ��ÿ��ͰΪ������ */
         B[i].head = B[i].tail = NULL;
     for (i = 0; i < N; ++i) { /* ��ԭʼ������������ʼ����List */
         tmp = (PtrToNode)malloc(sizeof(struct Node));
         tmp->key = A[i];
         tmp->next = List;
         List = tmp;
     }
     /* ���濪ʼ���� */
     for (D = 1; D <= MaxDigit; ++D) { /* �����ݵ�ÿһλѭ������ */
         /* �����Ƿ���Ĺ��� */
         p = List;
         while (p) {
             Di = GetDigit(p->key, D); /* ��õ�ǰԪ�صĵ�ǰλ���� */
             /* ��List��ժ�� */
             tmp = p; p = p->next;
             /* ����B[Di]��Ͱβ */
             tmp->next = NULL;
             if (B[Di].head == NULL)
                 B[Di].head = B[Di].tail = tmp;
             else {
                 B[Di].tail->next = tmp;
                 B[Di].tail = tmp;
             }
         }
         /* �������ռ��Ĺ��� */
         List = NULL;
         for (Di = Radix-1; Di >= 0; --Di) { /* ��ÿ��Ͱ��Ԫ��˳���ռ���List */
             if (B[Di].head) { /* ���Ͱ��Ϊ�� */
                 /* ��Ͱ����List��ͷ */
                 B[Di].tail->next = List;
                 List = B[Di].head;
                 B[Di].head = B[Di].tail = NULL; /* ���Ͱ */
             }
         }
     }
     /* ��List����A[]���ͷſռ� */
     for (i = 0; i < N; ++i) {
        tmp = List;
        List = List->next;
        A[i] = tmp->key;
        free(tmp);
     }
}

void MSD_Radix_Sort(ElementType A[], int N)
{
    MSD(A, 0, N-1, MaxDigit);
}
