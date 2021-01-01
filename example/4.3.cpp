//
// Created by sohne on 2020/12/5.
//
#include <iostream>
using namespace std;

typedef struct TreeNode *Tree;
struct TreeNode{
    int v;
    Tree right, left;
    int flag;
};

Tree NewNode(int V){
    Tree T = (Tree)malloc(sizeof(struct TreeNode));
    T->v = V;
    T ->left =  T->right  = NULL;
    T -> flag = 0;
    return T;
}

Tree insert(Tree T, int V){
    if (!T) T = NewNode(V);
    else{
        if (V > T->v){
            insert(T->right, V );
        } else if (V < T->v){
            insert(T->left, V);
        }
    }
    return T;
}

Tree MakeTree(int N){
    Tree T;
    int i,V;

    scanf("%d",&V);
    T = NewNode(V);
    for (i=1;i<N;i++){
        scanf("%d",&V);
        T = insert(T, V);
    }
    return T;
}


int check(Tree T,int V){
    if (T->flag){
        if (V<T->v) return check(T->left,V);
        else if (V>T->v) return check(T->right,V);
        return 0;
    }
    else{
        if (V == T->v){
            T->flag = 1;
            return 1;
        }else{
            return 0;
        }

    }

}


int Judge( Tree T, int N )
{
    int i, V, flag = 0;
    /* flag: 0代表目前还一致，1代表已经不一致*/
    scanf("%d",&V);
    if (V!=T->v) flag =1;
    else T->flag=1;
    for (i=1; i<N; i++) {
        scanf("%d", &V);
        if ( (!flag) && (!check(T, V)) ) flag = 1;
    }
    if (flag) return 0;
    else return 1;

}


void Reset(Tree T){
    if (T->left)Reset(T->left);
    else if (T->right)Reset(T->right);
    T->flag=0;
}

void FreeTree(Tree T){
    if (T->left) FreeTree(T->left);
    if (T->right) FreeTree(T->right);
    free(T);
}

int main()
{ int N, L, i;
   Tree T;
   scanf("%d", &N);
   while (N) {
       scanf("%d", &L);
       T = MakeTree(N);
       for (i=0; i<L; i++) {
           if (Judge(T, N))printf("Yes\n");
           else printf("No\n");
           ResetT(T); /*清除T中的标记flag*/
        }
        FreeTree(T);
        scanf("%d", &N);
    }

    return 0;
