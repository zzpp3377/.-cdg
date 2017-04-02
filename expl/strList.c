#include "strList.h"
#include <string.h>
#include <stdio.h>

//-----------------------------------------------------------------
//fucntion : pCreatStrList()
//output : Node * head    //NULL---失败
//-----------------------------------------------------------------
Node * pCreatStrList(){
    return pCreateList();   
}
//------------------------------------------------------------------
//fucniton : iPushStr()
//input : Node* head , char * str
//output : int           //0------成功，-1-----失败
//------------------------------------------------------------------
int iPushStr(Node * head,char * str){
    return iPush(head,(void*)str);
}
//------------------------------------------------------------------
//function : pPopStr()
//input : Node* head
//output : char * str   
//-----------------------------------------------------------------
char * pPopStr(Node* head){
    return (char*)pPop(head);
}
//----------------------------------------------------------------
//function: iSortStr()
//input : Node * head
//----------------------------------------------------------------
void vSortStr(Node* head){
    Node * max=NULL;
    Node *point=head;

    int i=0;
    int j=0;
    int len=0;
    while(point->next!=NULL){
        len++;
        point=point->next;
    }

    for(i=0;i<len;i++){
        max=head->next;
        point=head;
        for(j=0;j<len-i ;j++){ 
            point=point->next;
            if( strcasecmp((char *)point->pContent,(char *)max->pContent)>0 )max=point;
        }
        void * temp=max->pContent;
        max->pContent=point->pContent;
        point->pContent=temp;
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

//--------------------------------------------------------------------
//function : iIsEmptyStr()
//input : Node* head
//output : int          //1-----空，0------非空
//------------------------------------------------------------------
int iIsEmptyStr(Node* head){
    return iIsEmpty(head);
}
