//
// Created by sohne on 2020/11/19.
//

typedef struct PolyNode *Polynomial;
struct PolyNode{
    int  coef;
    int  expon;
    Polynomial link;
};

typedef struct LNode *List;
struct LNode{
    ElementType Data[MAXSIZE];
    int Last;
};
struct LNode L;//initalize LNiode
List PtrL;

//initalize
List MakeEmpty(){
    List Ptrl;
    Ptrl = (List)malloc(sizeof(struct LNode));
    PtrL->Last = -1;
    return PtrL;
}

//searching
int Find(ElementType X,List Ptrl){
    int i = 0;
    while (i<=PtrL->Last && PtrL->Data[i]!=X)
        i++;
    if (i>PtrL->Last) return -1;
    else return i;
}

void insert(ElementType X, int i, List PtrL)
{
    int j;
    if (PtrL->Last==MAXSIZE-1){
        printf("表满");
        return;
    }
    if(i<1||i>PtrL->Last+2){
        printf("位置不合法");
        return;
    }
    for (j=PtrL->Last;j>=i-1;j--){
        PtrL->Data[j+1] = PtrL->Data[j];
    }
    PtrL->Data[i-1] = X;
    PtrL->Last++;
    return;
}

void Delete(int i, List PtrL){
    int j;
    if (i<1 || i>PtrL->Last+1){
       printf("不存在第%d个元素");
        return;
    }
    for(j=i;j<PtrL->Last;j++){
        PtrL->Data[j-1] = PtrL->Data[j];
    }
    PtrL->Last--;
    return;
}