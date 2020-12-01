//
// Created by sohne on 2020/11/30.
//


//方法1：顺序查找
int SequentialSearch (StaticTable *Tbl, ElementType K)
{/*在表Tbl[1]~Tbl[n]中查找关键字为K的数据元素*/
    int i;
    Tbl->Element[0] =K;     /*建立哨兵*/
    for(i=Tbl->Length; Tbl->Element[i]!=K;i--);
    return i;
}


int BinarySearch ( StaticTable *Tbl, ElementType K){
    int right, left, mid, noFound = -1;
    left = 1;
    right = Tbl->Length;

    while (left<=right){
        mid = (right+left)/2;
        if (K<Tbl->Element[mid]) right = mid-1;
        else if (K>Tbl->Element[mid])left = mid+1;
        else return mid;
    }
    return noFound;
}
