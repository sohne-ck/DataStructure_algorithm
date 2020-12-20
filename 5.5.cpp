//
// Created by sohne on 2020/12/8.
//
#define MaxSize 1000

typedef int ElementType; /*默认元素可以用非负整数表示*/
typedef int SetName; /*默认用根结点的下标作为集合名称*/
typedef ElementType SetType[MaxSize]

SetName Find(SetName S, ElementType X){
    for (;S[X]>0;X=S[X]);
    return X
}

void Union(SetType X, SetName Root1, SetName Root2){
    X[Root2] = Root1;
}