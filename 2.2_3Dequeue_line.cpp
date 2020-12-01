//
// Created by sohne on 2020/11/24.
//
#include <iostream>
using namespace std;


struct Node{
    ElementType *Data;
    struct Node *Next;
};

struct QNode{
    struct QNode *front;
    struct QNode *rear;
};

typedef struct QNode *Dequeue;
Queue PtrQ;

ElementType DeleteQ(Queue PtrQ){
    struct Node *FrontCell;
    ElementType FrontElem;

    if (PtrQ->front == NULL){
        printf("队列为空");
        return ERROR;
    }

    FrontCell = PtrQ->front;
    if (PtrQ->front == PtrQ->rear){
        PtrQ->front = PtrQ->rear = NULL;
    }else{
        PtrQ->front = PtrQ->front->Next;
    }
    FrontElem = FrontCell->Data;
    free(FrontCell);
    return FrontElem;
}