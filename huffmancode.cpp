//
// Created by sohne on 2020/12/7.
//
#include <iostream>
using namespace std;

#define MaxData 1000;

typedef struct MinHeapStruct *MinHeap;
struct MinHeapStruct{
    ElementType *Elements;
    int Size;
    int Capacity;
};

MinHeap Create(int Maxsize){
    MinHeap H = malloc(sizeof(struct MinHeapStruct));
    H->Elements = malloc((Maxsize+1) * sizeof(ElementType));
    H->Size = 0;
    H->Capacity = Maxsize;
    H->Elements[0] = MaxData;
    return H;
}

int WPL( HuffmanTree T, int Depth )
{   if ( !T->Left && !T->Right )
        return (Depth*T->Weight);
    else /* 否则T一定有2个孩子 */
        return (WPL(T->Left, Depth+1)+ WPL(T->Right, Depth+1));
}


MinHeap H = CreateHeap( N ); /* 创建一个空的、容量为N的最小堆 */
H = ReadData( N ); /* 将f[]读入H->Data[]中 */
HuffmanTree T = Huffman( H ); /* 建立Huffman树 */
int CodeLen = WPL( T, 0 );
