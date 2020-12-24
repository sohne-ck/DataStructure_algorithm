//
// Created by sohne on 2020/12/24.
//

#include<iostream>
#include <stdlib.h>
using namespace std;


#define SUCCESS 1
#define UNSUCCESS 0
#define HASHSIZE 12
#define NULLKEY -32768
typedef bool Status ;
typedef struct
{
    int *elem;
    int count;
}HashTable;

int m = 0;   //the length of HashTable


//Initialize  of HashTable
Status InitHashTable(HashTable* H)
{
    int i;
    m = HASHSIZE;
    H->count = m;
    H->elem = (int*)malloc(m*sizeof(int));
    for(i = 0;i < m; i++)
    {
        H->elem[i] = NULLKEY;
    }
    return true;
}

//hash function
int Hash(int key)
{
    return key % m;
}

//Insert the elem to the Hahtable
void InsertHash(HashTable* H,int key)
{
    int addr = Hash(key);  //get the address of hash
    while(H->elem[addr] != NULLKEY)     //Conflict
        addr = (addr+1) % m;
    H->elem[addr] = key;
}


//search the key
Status searchHash(HashTable H,int key,int *addr)
{
    *addr = Hash(key);
    while(H.elem[*addr] != key)
    {
        *addr = (*addr+1) % m;
        if(H.elem[*addr] == NULLKEY || *addr == Hash(key))
            //return the origin
            return UNSUCCESS;
    }
    return SUCCESS;
}

int main()
{
    return 0;
}
