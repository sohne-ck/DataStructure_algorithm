//
// Created by sohne on 2020/11/24.
//

//多项加法运算
//采用不带头节点的的单向链表，按照指数递减的顺序排列各项
#include <iostream>
using namespace std;


struct PolyNode{
    int coef;//系数
    int expon;//指数
    struct PolyNode *link;
};

typedef struct PolyNode *Ploynomial;
Ploynomial P1,P2;


void Attach(int c, int e, Ploynomial *pRear){
    Ploynomial P;

    P = (Ploynomial)malloc(sizeof(struct PolyNode));
    P->coef = c;
    P->expon = e;
    P->link = NULL;

    (*pRear)->link = P;
    *pRear = P;

}



Ploynomial PolyAdd(Ploynomial P1, Ploynomial P2){
    Ploynomial front,rear,temp;
    int sum;
    rear = (Ploynomial)malloc(sizeof(struct PolyNode));
    front = rear;
    while (P1 && P2){
        switch (Compare(P1->expon,P2->expon)) {
            case 1:
                Attach(P1->coef, P1->expon, &rear);
                P1 = P1->link;
                break;

            case -1:
                Attach(P2->coef, P2->expon, &rear);
                P2 = P2->link;
                break;

            case 0:
                sum = P1->coef + P2->coef;
                if (sum) Attach(sum, P1->expon, &rear);
                P1 = P1->link;
                P2 = P2->link;
                break;
        }
    }

    for (;P1;P1 = P1->link) Attach(P1->coef, P1->expon, &rear);
    for (;P2;P2 = P2->link) Attach(P2->coef, P2->expon, &rear);

    rear->link = NULL;
    temp =front;
    front = front->link;
    free(temp);

    return front
}

