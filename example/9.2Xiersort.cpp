//
// Created by sohne on 2020/12/20.
//

void Shell_sort( ElementType A[], int N )
{ for ( D=N/2; D>0; D/=2 ) {
    /* 希尔增量序列 */
        for ( P = D; P < N; P++ ) {
            /* 插入排序 */
            Tmp = A[P];
            for ( i=P; i>=D && A[iD]>Tmp; i-=D )
                A[i] = A[iD];
            A[i] = Tmp;
        }
    }
}