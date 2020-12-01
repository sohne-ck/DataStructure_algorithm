//
// Created by sohne on 2020/11/19.
//


typedef struct LNode *List;
struct LNode{
    ElementType Data;
    List Next;
};
struct LNode L;
List PtrL;

//求表长
int Length(List PtrL){
    List p = PtrL;
    int j=0;
    while (p){
        p=p->Next;
        j++;
    }
    return j;

}

//searching<按照序号查找FindKth，按值Find>
List FindKth(int K,List PtrL){
    List p=PtrL;
    int i=1;
    while (p!=NULL&&i<K){
        p = p->Next;
        i++;
    }
    if(i==K)return p;/*返回指针*/
    else return NULL;
}


List Find(ElementType X, List PtrL){
    List p = PtrL;
    while (p!=NULL && p->Data!=X)
        p = p->Next;
    return p;
}

List Insert(ElementType X,int i, List PtrL){
    List p,s;
    if(i == 1){
        s = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        s->Next = PtrL;
        return s;
    }
    p = FindKth(i-1,PtrL);
    if(p==NULL){
        printf("参数i错");
        return NULL;
    } else{
        s = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        s->Next = p->Next;
        p->Next = s;
        return PtrL
    }
}

List Delete(int i,List PtrL){
    List p,s;
    if(i==1){
        s = PtrL;
        if (PtrL!=NULL) PtrL = PtrL->Next;
        else return NULL;
        free(S);
        return PtrL;
    }
    p = FindKth(i-1,PtrL);
    if (p==NUll){
        printf("第i - 1个几点不存在");
        return NULL;
    }else if(p->Next==NULL){
        printf("第i个结点存在");
        retrun NULL;
    }else{
        s = p->Next;
        p->Next = s->Next;
        free(s);
        return PtrL;
    }
}
