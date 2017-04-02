#ifndef _stdlib_h_

#define _stdlib_h_
#include<stdlib.h>

typedef struct Node{
    void * pContent;
    struct Node * next;
} Node;  


int iIsEmpty(Node * head);
Node * pCreateList();
int iInsert( Node *head, int index, void * pContent);
void * pRemove( Node * head,int index );
int iDeleteList( Node * head );
int iPush( Node * head, void * pContent );
void * pPop(Node * head);
int iAddLast( Node * head,void * pContent);
void* pRemoveLast(Node * head);

#endif

