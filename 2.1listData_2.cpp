//
// Created by sohne on 2020/11/19.
//


typedef struct GNode *GList;
struct GNode{
    int Tag;
    union{
        ElementType Data;
        GList *SubList;
    }URegion;
    GList *Next;
};

