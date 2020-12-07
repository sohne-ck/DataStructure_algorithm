//
// Created by sohne on 2020/12/6.
//
//#include <iostream>
//using namespace std;

#define MaxData 1000;

typedef struct HeapStruct *MaxHeap;
struct HeapStruct{
    ElementType *Elements;
    int Size;
    int Capacity;
};

MaxHeap Create(int Maxsize){
    MaxHeap H = malloc(sizeof(struct HeapStruct));
    H->Elements = malloc((Maxsize+1) * sizeof(ElementType));
    H->Size = 0;
    H->Capacity = Maxsize;
    H->Elements[0] = MaxData;
    return H;
}

MaxHeap Insert(MaxHeap H, ElementType item){
    int i;
    if (IsFull(H)){
        prinf("堆已满");
        return;
    }
    i = ++H->Size;
    /* i指向插入后堆中的最后一个元素的位置 */
    for (;H->Elements[i/2]<item;i/2){
        H->Elements[i] = H->Elements[i/2];/* 向下过滤结点 */
        //H->Element[ 0 ] 是哨兵元素， 它不小于堆中的最大元素， 控制顺环结束。
    }
    H->Elements[i] = item /* 将item 插入 */
}
//T (N) = O ( log N )


ElementType DeletMax(MaxHeap H){
    /* 从最大堆H中取出键值为最大的元素，并删除一个结点 */
    int Parent,Child;
    ElementType MaxItem, temp;
    if (IsFull(H)){
        prinf("???");
        return;
    }
    MaxItem = H->Elements[1];/* 取出根结点最大值 */
    /* 用最大堆中最后一个元素从根结点开始向上过滤下层结点 */
    temp = H->Elements[H->Size--];
    for (Parent=1;Parent*2 <= H->Size; Parent=Child){
        Child = Parent * 2;
        if ((Child!=H->Size)&&(H->Elements[Child]<H->Elements[Child+1])){
            Child++;/* Child指向左右子结点的较大者 */
        }
        if (temp>=H->Elements[Child]) break;
            /* 移动temp元素到下一层 */
        else{H->Elements[Parent] = H->Elements[Child];}
    }
    H->Elements[Parent] = temp;
    return MaxItem
}
