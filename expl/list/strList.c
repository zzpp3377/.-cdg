#include "strlist.h"
#include <string.h>
#include <stdio.h>
//-----------------------------------------------------------------
//fucntion : pCreatStrList()
//output : Node * head    //NULL---失败
//-----------------------------------------------------------------
Node * pCreatStrList(
    return pCreateList();        
)
//------------------------------------------------------------------
//fucniton : iPushStr()
//input : Node* head , char * str
//output : int           //0------成功，-1-----失败
//------------------------------------------------------------------
int iPushStr(Node * head,char * str){
    return iPush(head,(void*)content);
}
//------------------------------------------------------------------
//function : pPopStr()
//input : Node* head
//output : char * str
//-----------------------------------------------------------------
char * pPopStr(Node* head){
    reutrn (char*)pPop(head);
}
//----------------------------------------------------------------
//function: iSortStr()
//input : Node * head
//----------------------------------------------------------------
void vSortStr(Node* head){
    Node * max=head;
    Node *point=head;

    int i=0;
    int j=0;
    int len=0;
    while(point->next!=NULL){
        len++;
        point=point->next;
    }

    for(i=0,point=head ;i<len ;i++){
        for(j=0,point=head ;j<len-i ;j++){ 
            point=point->next;
            if( stricomp(point->pContent,max->pContent) )max=point;
        }
        void * temp=max->pContent;
        max->pContent=point->pContent;
        point-->pContent=temp;
    }
}
//-----------------------------------------------------------------
//function : iDeleteListStr()
//input : Node * head
//output : int            //0-----成功，1-----失败
//-----------------------------------------------------------------
int iDeleteListStr(Node* head){
    return iDeleteList(head);
}


