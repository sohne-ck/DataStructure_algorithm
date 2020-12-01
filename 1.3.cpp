//
// Created by sohne on 2020/11/23.
//
#include<iostream>
using namespace std;

int MaxSubseqSum1( int A[], int N ){
    int ThisSum, MaxSum = 0;
    int i,j,k = 0;
    for(i=0;i<N;i++){
        for(j=i;j<N;j++){
            ThisSum = 0;
            for(k=i;k<j;k++){
                ThisSum+=A[k];
            }
            if (ThisSum>MaxSum){
                MaxSum = ThisSum;
            }
        }
    }
    return MaxSum;
}


int MaxSubseqSum2( int A[], int N ){
    int ThisSum, MaxSum = 0;
    int i,j = 0;
    for (i=0;i<N;j++){
        for (j=i;j<N;j++){
            ThisSum += A[j];
            if (ThisSum>MaxSum){
                MaxSum = ThisSum;
            }
        }
    }
    return MaxSum;
}




int crossMax(int A[],int left, int right, int mid){
    int leftsum, rightsum = 0;
    int leffisum = A[mid];
    int rigfisum = 0;
    int i = 0;
    for (i=left; i>=0; i--){
        leftsum += A[i];
        if (leftsum>leffisum){
            leffisum = leftsum;
        }
    }
    for (i=mid+1; i<=right; i++){
        rightsum += A[i];
        if (rightsum >rigfisum){
            rigfisum = rightsum;
        }
    }
    return leffisum+rigfisum;
}

int max(int a,int b){
    return a>b?a:b;
}



int MaxSubseqSum3( int A[],int left,int right ){//left-->0, right-->max

    if (left==right) { return A[left];}

    int mid = (left+right)/2;
    int leftsum = MaxSubseqSum3(A, left, mid);
    int rightsum = MaxSubseqSum3(A, mid+1, right);
    int cross = crossMax(A,left,right,mid);

    return max(max(leftsum,rightsum),cross);
}


int MaxSubseqSum4( int A[], int N ){
    int ThisSum, MaxSum = 0;
    int i;
    for (i=0; i<N; i++){
        if (ThisSum>MaxSum)
            MaxSum = ThisSum ;
        else if(ThisSum<0){
            MaxSum=0;
        }
    }
}