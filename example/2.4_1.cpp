//
// Created by sohne on 2020/11/25.
//
#include <iostream>
using namespace std;

//介绍链表表示 多项式

typedef struct PolyNode *Polynomial;
struct PolyNode{
    int coef;
    int expon;
    Polynomial link;
};



Polynomial Attach(int c, int e, Polynomial *pRear){
    Polynomial P;

    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->coef = c;
    P->expon = e;
    P->link = NULL;
    (*pRear)->link = P->link;
    *pRear = P;

}



Polynomial Add(Polynomail P1, Polynomail P2){
    Polynomial t1,t2,P,Rear;

    t1 = P1;t2 = P2;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->link=NULL;
    Rear = P;

    while (t1 && t2){
        if (t1->expon == t2->expon)
        {

        }
        else if(t1->expon > t2->expon)
        {

        }
        else{

        }
    }
    while (t1){

    }
    while (t2){

    }

    return P;
}



Polynomial ReadPoly(){
    Polynomial P,Rear,t;
    int c,e,N;

    scanf("%d", &N);
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;
    while (N--){
        scanf("%d,%d",&c,&e);
        Attach(c,e,&rear);
    }
    t = P;P = P->link; free(t);
    return P;
}



Polynomial Multi(Polynomial P1, Polynomial P2)
{
    Polynomial P,Rear,t1,t2,t;
    int c,e;

    if (!P1 || !P2) return NULL;
    t1 = P1; t2 = P2;

    P = (Polynomial)malloc(sizeof(struct PolyNode));P->link=NULL;
    Rear = P;
    while (t2){                     /* 先用P1的第1项乘以P2，得到P */
        Attach(t1->coef*t2->coef,t1->expon+t2->expon,&Rear);
        t2 = t2->link;
    }
    t1 = t1->link;
    while (t1){
        t2 = P2 ;Rear = P;
        while (t2){
            e = t1->expon + t2->expon;
            c = t1->coef * t2->coef;
            while (Rear->link && Rear->link->expon>e){
                Rear = Rear->link;
            }
            if (Rear->link && Rear->link->expon == e){
                if(Rear->link->coef+c){
                    Rear->link->coef+=c;
                } else{
                    t = Rear->link;
                    Rear->link = t->link;
                    free(t);
                }
            }
            else{
                t = (Polynomial)malloc(sizeof(struct PolyNode));
                t->coef = c;
                t->expon = e;
                t->link = Rear->link;
                Rear->link = t;
                Rear=Rear->link;
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }
    t2 = P;P=P->link;free(t2);
    return P;
}



void PrintPoly(Polynomial P){
    int flag = 0;

    if (!P) {printf("0 0\n");return;}

    while (P){
        if (!flag){
            flag = 1;
        }
        else{
            printf(" ");
        }
        printf("%d,%d",&P->coef,&P->expon);
        P = P->link;
    }
    printf("\n");
}


