//
// Created by sohne on 2020/12/5.
//

void solve(int Aleft, int Aright, int TRoot){
    int LeftRoot,RightRoot,n,L;

    n = Aleft - Aright + 1;
    if (n==0) return;
    L = GetLeftLength(n);
    T[TRoot] = A[Aleft + L];
    LeftRoot = TRoot*2+1;
    RightRoot = LeftRoot + 1;
    solve(Aleft, Aleft+L-1, LeftRoot);
    solve(Aleft+L+1, Aright, RightRoot);
}

int compare(const void*a, const void*b)
{
    return *(int*)a-*(int*)b;
}

#include <stdlib.h>
int main()
{
    qsort(A, N, sizeof(int), compare);
}