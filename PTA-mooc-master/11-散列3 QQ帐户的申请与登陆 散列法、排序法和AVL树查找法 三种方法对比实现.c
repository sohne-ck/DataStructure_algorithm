/**
* ��Ӧ�γ�����11.3
* �Ը�����ʹ����ɢ�з��������򷽷���AVL���������ַ��������˱Ƚ�
* �������򷽷���AVL�����ҷ����Ե�1��2����ʱ��˵�����ڱ��⣬�����ַ�������Զ����ɢ�з���
* ���򷽷��У���ѯĳһԪ���Ƿ����ʹ���˶��ֲ��ң���ÿ����һ�����û���Ҫ����һ��qsort����
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define QQSMALLEST 4
#define QQLENGTH 10
#define PWLENGTH 16
#define MAXD 5
#define MAXTABLESIZE 1000000

#define NOTFOUND -1

typedef struct UserInfoNode UserInfo;
struct UserInfoNode {
    char qq[QQLENGTH + 1];
    char password[PWLENGTH + 1];
};

typedef UserInfo ElementType;
/* ������������HashTable��ض��忪ʼ������������ */
typedef int Index;

typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode Position;

typedef struct LHNode *PtrToLHNode;
struct LHNode {
    PtrToLNode Next;
};
typedef PtrToLHNode List;

typedef struct TblNode *HashTable;
struct TblNode {
    int TableSize;
    List Heads;
};

int NextPrime(int N);   // ���ش���N�Ҳ�����MAXTABLESIZE����С����
int Hash(char *Key, int p);

HashTable CreateTable(int TableSize);
Position Find(HashTable H, ElementType Key);
bool Insert(HashTable H, ElementType Key);
void DestoryTable(HashTable H);
/* ������������HashTable��ض������������������ */

/* ��������������������غ������忪ʼ������������ */
int comp(const void *a, const void *b);
int binarySearch(UserInfo *arr, int user_Num, UserInfo *info);    // ���Ҳ��ö��ַ�
bool Sort_Item(UserInfo *arr, int *user_Num, UserInfo *info);    // �������򷽷�ʹ�������Ԫ������
/* ��������������������غ���������������������� */

/* ������������AVL����ض��忪ʼ������������ */
typedef struct TreeNode *AVLTree;
struct TreeNode {
    UserInfo info;
    AVLTree Left, Right;
};
int getHeight( AVLTree T );
AVLTree RR( AVLTree T );
AVLTree LL( AVLTree T );
AVLTree RL( AVLTree T );
AVLTree LR( AVLTree T );
AVLTree Search(AVLTree T, UserInfo *info);    // δ�ҵ�����NULL
AVLTree InsertAVL( AVLTree T, UserInfo *info );  // ����ɹ������µ�������㣬���򷵻�NULL
void FreeTree( AVLTree T );
/* ������������AVL����ض��忪ʼ������������ */
void HandleInput(); // ��������

void HashTableHandle(int N); // ʹ��HashTable������
void HashTableCheck(HashTable H, char flag, UserInfo *info);    // ��ÿһ��ָ����д���

void SortHandle(int N); // ʹ�����򷽷����������Ե�1��2��ͨ�������г�ʱ
int SortCheck(UserInfo *arr, int user_Num, char flag, UserInfo *info);   // ��ÿһ��ָ����ж��ֲ��Ҵ������ص�ǰ�û���

void AVLHandle(int N);  // ʹ��AVL��������
AVLTree AVLCheck(AVLTree T, char flag, UserInfo *info); // ����ִ�����ָ����µ�AVL�����ڵ�

int main()
{
    HandleInput();

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

int Hash(char *Key, int P)
{
    int tmp;
    if (strlen(Key) == QQSMALLEST)
        tmp = atoi(Key);
    else
        tmp = atoi(Key + strlen(Key) - MAXD);
    return tmp % P;
}

HashTable CreateTable(int TableSize)
{
    HashTable H;
    int i;
    H = (HashTable)malloc(sizeof(struct TblNode));
    H->TableSize = NextPrime(TableSize);
    H->Heads = (List)malloc(H->TableSize * sizeof(struct LNode));
    for (i = 0; i < H->TableSize; ++i) {
        H->Heads[i].Next = NULL;
    }
    return H;
}

Position Find(HashTable H, ElementType Key)
{
    Position P;
    Index Pos;

    Pos = Hash(Key.qq, H->TableSize);

    P = H->Heads[Pos].Next;
    while(P && strcmp(P->Data.qq, Key.qq))
        P = P->Next;
    return P;
}

bool Insert(HashTable H, ElementType Key)
{
    Position P, NewCell;
    Index Pos;

    P = Find(H, Key);
    if (!P) {
        NewCell = (Position)malloc(sizeof(struct LNode));
        strcpy(NewCell->Data.qq, Key.qq);
        strcpy(NewCell->Data.password, Key.password);
        Pos = Hash(Key.qq, H->TableSize);
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell;
        return true;
    }
    else
        return false;
}

void DestoryTable(HashTable H)
{
    int i;
    Position P, Tmp;

    for (i = 0; i < H->TableSize; ++i) {
        P = H->Heads[i].Next;
        while (P) {
            Tmp = P->Next;
            free(P);
            P = Tmp;
        }
    }
    free(H->Heads);
    free(H);
}

int comp(const void *a, const void *b)
{
    char *str1, *str2;
    int size1, size2;
    str1 = ((UserInfo *)a)->qq; str2 = ((UserInfo *)b)->qq;
    size1 = strlen(str1); size2 = strlen(str2);
    if (size1 == size2)
        return strcmp(str1, str2);
    else
        return size1 < size2 ? -1 : 1;
}

int binarySearch(UserInfo *arr, int user_Num, UserInfo *info)
{
    int low, mid, high, ans;
    low = 0; high = user_Num;
    while (low <= high) {
        mid = (low + high) >> 1;
        ans = comp(arr + mid, info);
        if (ans > 0)
            high = mid - 1;
        else if (ans < 0)
            low = mid + 1;
        else return mid;
    }
    return NOTFOUND;
}

bool Sort_Item(UserInfo *arr, int *user_Num, UserInfo *info)
{
    int pos;
    pos = binarySearch(arr, *user_Num, info);
    if (pos == -1) {
        strcpy(arr[*user_Num].qq, (*info).qq);
        strcpy(arr[*user_Num].password, (*info).password);
        ++(*user_Num);
        qsort(arr, *user_Num, sizeof(UserInfo), comp);
        return true;
    }
    return false;
}

int getHeight( AVLTree T )
{
    if (!T) return 0;
    int lHeight, rHeight;
    lHeight = getHeight(T->Left);
    rHeight = getHeight(T->Right);
    return (lHeight > rHeight ? lHeight : rHeight) + 1;
}

AVLTree RR( AVLTree T )
{
    AVLTree tmp;
    tmp = T->Right;
    T->Right = tmp->Left;
    tmp->Left = T;
    return tmp;
}

AVLTree LL( AVLTree T )
{
    AVLTree tmp;
    tmp = T->Left;
    T->Left = tmp->Right;
    tmp->Right = T;
    return tmp;
}

AVLTree RL( AVLTree T )
{
    AVLTree tmp1, tmp2;
    tmp1 = T->Right;
    tmp2 = tmp1->Left;
    tmp1->Left = tmp2->Right;
    T->Right = tmp2->Left;
    tmp2->Left = T;
    tmp2->Right = tmp1;
    return tmp2;
}

AVLTree LR( AVLTree T )
{
    AVLTree tmp1, tmp2;
    tmp1 = T->Left;
    tmp2 = tmp1->Right;
    tmp1->Right = tmp2->Left;
    T->Left = tmp2->Right;
    tmp2->Left = tmp1;
    tmp2->Right = T;
    return tmp2;
}

AVLTree Search(AVLTree T, UserInfo *info)
{
    int ans;
    if (!T) return NULL;
    else {
        ans = comp(&(T->info), info);
        if (ans == 0) return T;
        else if (ans > 0) return Search(T->Left, info);
        else return Search(T->Right, info);
    }
}

AVLTree InsertAVL( AVLTree T, UserInfo *info )
{
    int ans;

    if (!T) {
        T = (AVLTree)malloc(sizeof(struct TreeNode));
        strcpy(T->info.qq, info->qq);
        strcpy(T->info.password, info->password);
        T->Left = T->Right = NULL;
    }
    else {
        ans = comp(info, &(T->info));
        if (ans > 0) {
            T->Right = InsertAVL(T->Right, info);
            if (getHeight(T->Left) - getHeight(T->Right) == -2) {
                if (comp(info, &(T->Right->info)) > 0)  T = RR(T);
                else    T = RL(T);
            }
        }
        else if (ans < 0) {
            T->Left = InsertAVL(T->Left, info);
            if (getHeight(T->Left) - getHeight(T->Right) == 2) {
                if (comp(info, &(T->Left->info)) < 0)  T = LL(T);
                else    T = LR(T);
            }
        }
    }
    return T;
}

void FreeTree( AVLTree T )
{
    if (T->Left) FreeTree(T->Left);
    if (T->Right) FreeTree(T->Right);
    free(T);
}

void HandleInput()
{
    int N;
    scanf("%d", &N);
    HashTableHandle(N);
}

void HashTableHandle(int N)
{
    int i; char flag;
    UserInfo info;
    HashTable H;

    H = CreateTable(N);
    for (i = 0; i < N; ++i) {
        scanf("\n%c %s %s", &flag, info.qq, info.password);
        HashTableCheck(H, flag, &info);
    }
    DestoryTable(H);
}

void HashTableCheck(HashTable H, char flag, UserInfo *info)
{
    Position pos;
    if (flag == 'N') {
        if (Insert(H, *info)) printf("New: OK");
        else printf("ERROR: Exist");
    }
    else {
        pos = Find(H, *info);
        if (pos) {
            if (strcmp(info->password, pos->Data.password))
                printf("ERROR: Wrong PW");
            else printf("Login: OK");
        }
        else printf("ERROR: Not Exist");
    }
    printf("\n");
}

void SortHandle(int N)
{
    int i, user_Num; char flag;
    UserInfo info, *arr;
    user_Num = 0;
    arr = (UserInfo *)malloc(N * sizeof(UserInfo));
    for (i = 0; i < N; ++i) {
        scanf("\n%c %s %s", &flag, info.qq, info.password);
        user_Num = SortCheck(arr, user_Num, flag, &info);
    }
    free(arr);
}

int SortCheck(UserInfo *arr, int user_Num, char flag, UserInfo *info)
{
    int pos;
    if (flag == 'N') {
        if (Sort_Item(arr, &user_Num, info))  printf("New: OK");
        else printf("ERROR: Exist");
    }
    else {
        pos = binarySearch(arr, user_Num, info);
        if (pos != -1) {
            if (strcmp(info->password, arr[pos].password))
                printf("ERROR: Wrong PW");
            else printf("Login: OK");
        }
        else printf("ERROR: Not Exist");
    }
    printf("\n");
    return user_Num;
}

void AVLHandle(int N)
{
    int i; char flag;
    UserInfo info;
    AVLTree T;

    T = NULL;
    for (i = 0; i < N; ++i) {
        scanf("\n%c %s %s", &flag, info.qq, info.password);
        T = AVLCheck(T, flag, &info);
    }
    FreeTree(T);
}

AVLTree AVLCheck(AVLTree T, char flag, UserInfo *info)
{
    AVLTree pos;

    pos = Search(T, info);
    if (flag == 'N') {
        if (!pos) {
            T = InsertAVL(T, info);
            printf("New: OK");
        }
        else printf("ERROR: Exist");
    }
    else {
        if (pos) {
            if (strcmp(info->password, pos->info.password))
                printf("ERROR: Wrong PW");
            else printf("Login: OK");
        }
        else printf("ERROR: Not Exist");
    }
    printf("\n");
    return T;
}
