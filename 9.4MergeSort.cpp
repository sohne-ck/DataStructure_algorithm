//
// Created by sohne on 2020/12/20.
//

/* L = 左边起始位置, R = 右边起始位置, RightEnd = 右边终点位置 */
void Merge(ElementType A[],ElementType TmpA[],int R, int L, int RightEnd) {
    int LeftEnd = R - 1; /* 左边终点位置。假设左右两列挨着 */
    int Tmp = L; /* 存放结果的数组的初始位置 */
    int NumElements = RightEnd - L + 1;
    if (L<=LeftEnd&&R<=RightEnd){
        if A[L]<A[R] TmpA[Tmp++] = A[L++]
    }
    while (L<LeftEnd){
        TmpA[Tmp++] = A[L++]
    }
    while (R<RightEnd){
        TmpA[Tmp++] = A[R++]
    }
    for (i=0;i<NumElements;i++,RightEnd--)
        A[RightEnd] = TmpA[RightEnd];
}

//递归算法
// 分而治之
void Merge_pass( ElementType A[], ElementType TmpA[], int N, int length ) /* length = 当前有序子列的长度 */
{ for ( i=0; i <= N–2*length; i += 2*length )
        Merge1( A, TmpA, i, i+length, i+2*length–1 );
    if ( i+length < N ) /* 归并最后2个子列 */
        Merge1( A, TmpA, i, i+length, N–1);
    else /* 最后只剩1个子列 */
    for ( j = i; j < N; j++ )
        TmpA[j] = A[j];
}

//非递归算法
void Merge_sort( ElementType A[], int N )
{ int length = 1; /* 初始化子序列长度 */
    ElementType *TmpA;
    TmpA = malloc( N * sizeof( ElementType ) );
    if ( TmpA != NULL ) {
        while( length < N ) {
            Merge_pass( A, TmpA, N, length );
            length *= 2;
            Merge_pass( TmpA, A, N, length );
            length *= 2;
        }
        free( TmpA );
    }
    else Error( "空间不足");
}