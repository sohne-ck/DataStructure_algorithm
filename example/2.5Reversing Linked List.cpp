//
// Created by sohne on 2020/11/30.
//
//
typedef struct PtrNode *Ptr;
struct PtrNode{
    struct PtrNode *Data;
    struct PtrNode *next;
};

Ptr Reverse(Ptr head, int k){
    Ptr tn,to,tmp;
    int cnt = 0;
    tn = head->next;
    to = tn->next;

    while (cnt<k){
        tmp = to->next;

        to->next = tn;

        tn = to; to = tmp;
        cnt++;
    }
    head->next->next = to;
    return tn;
}