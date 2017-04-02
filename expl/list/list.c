#include "stdlib.h"
#include "list.h"
//----------------------------------------------------
//function : iIsEmpty
//input : Node* head
//output : int       ///1----empty,0----not empty
//----------------------------------------------------
int iIsEmpty(Node * head){
    return head->next==NULL;
}

//function : pCreateList()
//---------------------------------------------------
Node* pCreateList(){
   Node *head = (Node *)malloc( sizeof(Node) );
   if(head==NULL) return NULL;
   head->pContent = NULL;
   head->next=NULL;
   return head;
}

//------------------------------------------------
//function : iInsert()
//input : Node * head, int index , void * pContent
//output : int realindex
//-----------------------------------------------
int iInsert( Node *head, int index, void * pContent){
    int i=0;
    Node* node=NULL;
    Node* point=head;

    if( head==NULL || pContent==NULL ) return -1;
    if(index<0) index=0;
    node = (Node*)malloc( sizeof(Node) );
    if(node==NULL) return -1;
    node->pContent=pContent;
    
    for( i=0 ; (i<index) && (point->next!=NULL) ; i++ ) 
        point=point->next;

    node->next=point->next;
    point->next=node;
    return i;
}
//------------------------------------------------------
//function : pRemove()
//input : Node * head, int index
//ouput : void * pRemoveContent
//-----------------------------------------------------
void * pRemove( Node * head,int index ){
    int i=0;
    Node* point=head;
    Node* pRemoveNode=NULL;
    void* pRemoveContent=NULL;

    if( head==NULL || index<0 ) return NULL;
    if( iIsEmpty(head) )return NULL;

    for( i=0; i<index ; i++){
        point=point->next;
        if( point->next==NULL )return NULL;
    }

    pRemoveNode=point->next;
    point->next=point->next->next;
    pRemoveContent=pRemoveNode->pContent;
    free(pRemoveNode);
    return pRemoveContent;
}
//---------------------------------------------------------
//function : pDeleteList()
//input : Node* head
//output : int             ///0-----成功，-1------失败
//----------------------------------------------------------
int iDeleteList( Node* head ){
    if( head==NULL || head->next!=NULL ) return -1;
    free(head);
    return 0;
} 

//------------------------------------------------------
//function : iPush()
//input : Node* head, void * pContent
//output : int             ///0------成功，-1-----失败
//-----------------------------------------------------
int iPush( Node* head, void* pContent ){
    return iInsert( head,0,pContent );
}

//--------------------------------------------------------
//function : pPop()
//intput : Node* head
//output : void* pRemoveContent
//------------------------------------------------------
void * pPop(Node* head){
    return pRemove(head,0);
}

//-------------------------------------------------------
//function : iAddLast()
//input : Node* head,void* pContent
//output : int              ///0------成功，-1-----失败
//-------------------------------------------------------
int iAddLast( Node* head,void* pContent){
    Node* node=NULL;
    Node* point=head;

    if( head==NULL || pContent==NULL )return -1;
    node = (Node*)malloc(sizeof(Node));
    if(node==NULL)return -1;
    node->pContent=pContent;
    node->next=NULL;
    while( point->next!=NULL )point=point->next;
    point->next=node;
    return 0;
}

//------------------------------------------------------
//function : pRemoveLast()
//input : Node* head
//ouput : void* pRemoveContent
//-----------------------------------------------------
void* pRemoveLast(Node* head){
    Node* point=head;
    Node* pRemoveNode=NULL;
    void* pRemoveContent=NULL;

    if(head==NULL)return NULL;
    if( iIsEmpty(head) )return NULL;
    while( point->next->next!=NULL )point=point->next;

    pRemoveNode=point->next;
    point->next=NULL;
    pRemoveContent=pRemoveNode->pContent;
    free(pRemoveNode);
    return pRemoveContent;
}








