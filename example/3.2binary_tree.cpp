//
// Created by sohne on 2020/11/30.
//

//链式存储
typedef struct TreeNode *BinTree;
typedef BinTree Position;
struct TreeNode{
    int Data;
    BinTree left;
    BinTree right;
};