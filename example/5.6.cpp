//
// Created by sohne on 2020/12/8.
//

#include <iostream>
using namespace std;

#define MAXN 1001
#define MINH -1001

int H[MAXN],size;

void creat(){
    size = 0;
    H[o] = MINH
    /*设置“岗哨”*/
}

void Insert(int X){
    /* 将X插入H。这里省略检查堆是否已满的代码 */
    int i;
    for (i=++size;H[i/2]>X;i/2)
        H[i] = H[i/2];
    H[i] = X;
}

int main(){
//    读入n和m
//    根据输入序列建堆
//    对m个要求：打印到
//            根的路径
    int n,m,j,i;

    scanf("%d %d", &n, &m);
    creat();
    for (i=0;i<n;i++){
        scanf("%d",&X);
        Insert(X);
    }
    for (i=0;i<m;i++){
        scanf("%d",&j);
        printf("%d",&H[j]);
        while (j>1){
            j/=2;
            printf("%d",&H[j]);
        }
        printf("/n");
    }

    return 0;
}