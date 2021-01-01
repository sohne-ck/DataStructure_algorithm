//
// Created by sohne on 2020/11/23.
//
#include<iostream>
using namespace std;

//堆栈
#define MaxSize 100
typedef struct SNode *Stack;
struct SNode{
    ElementType Data[MaxSize];
    int Top;
};


void Push( Stack PtrS, ElementType item ){
    if (PtrS->Top>=MaxSize){
        printf("堆栈已满");
        return;
    } else{
        PtrS->Data[++(PtrS -> Top)]=item;
        return;
    }
}

ElementType Pop( Stack PtrS ){
    if (PtrS->Top==-1){
        printf("该栈已空");
        return 0;
    } else{
        return PtrS->Data[(PtrS->Top)--];
    }
}


//双向链表
//typedef struct DStack *Stack;
struct DStack{
    ElementType Data[MaxSize];
    int Top1;
    int Top2;
}S;

void Push(struct DStack *Ptrs, ElementType item, int Tag){
    /* Tag作为区分两个堆栈的标志，取值为1和2 */
    if (Ptrs->Top2-Ptrs->Top1 == 1){
        printf("该栈溢出");
        return;
    }
    if (Tag == 1){
        Ptrs->Data[++(Ptrs->Top1)] == item;
    } else{
        Ptrs->Data[--(Ptrs->Top2)] == item;
    }
}

ElementType Pop( struct DStack *PtrS, int Tag ){
    /* Tag作为区分两个堆栈的标志，取值为1和2 */
    if (Tag==1){
        if (PtrS -> Top == -1){
            printf("Top1 空");return NULL;
        } else{
            return PtrS -> Data[(PtrS->Top1)--];
        }
    } else{
        if (PtrS -> Top2 == MaxSize){
            printf("Top2 空");return NULL;
        } else{
            return PtrS->Data[(PtrS->Top2)++]
        }
    }
}


