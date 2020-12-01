//
// Created by sohne on 2020/11/30.
//

#include <iostream>
#include<string.h>
#include<stack>
using namespace std;

#define MaxSize 1000

typedef struct TreeNode *BinTree;
typedef BinTree Position;
struct TreeNode{
    int Data;
    BinTree left;
    BinTree right;
};

struct BTNode{
    BinTree btnode;
    bool isFirst;
};


void ProOrderTraversal(BinTree BT){
    if (BT){
        printf("%d",BT->Data);
        ProOrderTraversal(BT->left);
        ProOrderTraversal(BT->right);
    }
}

void InOrderTraversal(BinTree BT){
    if (BT){
        InOrderTraversal(Bt->left);
        printf("%d",BT->Data);
        InOrderTraversal(BT->right);
    }
}

void PostOrderTraversal(BinTree BT){
    if (BT){
        PostOrderTraversal(BT->left);
        PostOrderTraversal(BT->right);
        printf("%d",BT->Data);
    }
}


//非递归解法

//中序
void InOrderTraversalNew(BinTree BT){
    BinTree T = BT;
    Stack S = CreateStack(MaxSize);
    while (T||!IsEmpty(S)){
        while (T){
            Push(S,T);
            T = T->left;
        }
        while (!IsEmpty(S)){
            T = Pop(S);
            printf("%5d",T->Data);
            T = T->right;
        }
    }
}

//先序
void ProOrderTraversalNew(BinTree BT){
    BinTree T = BT;
    Stack S = CreateStack(MaxSize);
    while (T||!IsEmpty(S)){
        while (T){
            printf("%5d",T->Data);
            Push(S,T);
            T = T->left;
        }
        while (!IsEmpty(S)){
            T = Pop(S);
            T = T->right;
        }
    }
}

//后序遍历
//判断其出现次数

void PostOrderTraversalNew(BinTree BT){
    BinTree  T = BT;
    Stack S = CreateStack(MaxSize);
    BTNode *tmp;
    while (T||!isEmpty(S)){
        while (T){
            BTNode *btn = (BTNode *)malloc(sizeof(BTNode));
            btn->btnode = T;
            btn->isFirst = true;
            push(btn);
            T = T->left;
        }
        if (!isEmpty(S)){
            tmp = top(S);
            if (tmp->isFirst) {
                tmp->isFirst = false;
                push(tmp);
                T = T->right;
                T = tmp->btnode->right;
            } else{
                printf(str(tmp->btnode->Data));
                T = NULL;
            }
        }

    }
}

//层序遍历
void levelOrderTraversal(BinTree BT){
    Queue Q;BinTree T;
    if (!BT) return;//空树
    Q = CreatQueue(MaxSize);//创建新的队列
    AddQ(Q, BT);
    while (!IsEmptyQ(Q)){
        T = DeleteQ(Q);
        printf("%d\n",T->Data);
        if (T->left) AddQ(Q, T->left);
        if (T->right) AddQ(Q, T->right);
    }
}


//查找根结点
void PreOrderPrintLeaves(BinTree BT){
    if (BT){
        if (!BT->left && !BT->right){
            printf("%d",BT->Data);
        }
        PreOrderPrintLeaves(BT->left);
        PreOrderPrintLeaves(BT->right);
    }
}

//二叉树的高度
int PostOrderGetHeight(BinTree BT){
    int HR, HL, MaxH;
    if(BT){
        HL = PostOrderGetHeight(BT->left);
        HR = PostOrderGetHeight(BT->right);
        MaxH = (HL>HR)?HL:HR;
        return (MaxH + 1);
    }
    else return 0;
}


