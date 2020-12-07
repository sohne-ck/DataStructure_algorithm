//
// Created by sohne on 2020/12/7.
//

typedef struct {
    ElementType Data;
    int Parent;
}SetType;

//负数表示根结点；
//非负数表示双亲结点的下标。

int Find( SetType S[ ], ElementType X ) {
    /* 在数组S中查找值为X的元素所属的集合 */
    /* MaxSize是全局变量，为数组S的最大长度 */
    int i;
    for (i=0; i<MaxSize&&S[i].Data!=X; i++);
    if (i>MaxSize) return -1;
    for (;S[i].Parent>=0;i = S[i].Parent);
    return i;
}

void Union( SetType S[ ], ElementType X1, ElementType X2 ){
    int Root1, Root2;
    Root1 = Find(S, X1);
    Root2 = Find(S, X2);

    if (Root1!=Root2) S[Root2].Parent = Root1;
}