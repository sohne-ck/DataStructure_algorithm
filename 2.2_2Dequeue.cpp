//
// Created by sohne on 2020/11/24.
//
#include <iostream>
using namespace std;

#define MaxSize 100
typedef struct QNode *Queue;

struct QNode{
    ElementType Data[MaxSize];
    int rear;
    int front;
};


Queue CreatQueue(int size){
    //生成长度为MaxSize的空队列；
    }

int IsFullQ( Queue Q, int size){
    //判断队列Q是否已满；
}

void AddQ( Queue PtrQ, ElementType item ){
    //将数据元素item插入队列Q中；
    if ((PtrQ->rear+1)%MaxSize == PtrQ->front){
        printf("堆栈已满");
        return;
    }
    PtrQ->rear = (PtrQ->rear+1)%MaxSize;
    PtrQ->Data[PtrQ->rear] = item;
}

int IsEmptyQ( Queue Q ){
    //判断队列Q是否为空；
}

ElementType DeleteQ( Queue PtrQ ) {
    //将队头数据元素从队列中删除并返回。
    if (PtrQ->front==PtrQ->rear){
        printf("队列为空");
        return ERROR;
    } else{
        PtrQ->front = (PtrQ->front+1)%MaxSize;
        return PtrQ->Data[PtrQ->front];
    }

}
