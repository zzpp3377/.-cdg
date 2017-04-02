 #ifndef _strList_h_
#define _strList_h_

#include "list.h"

Node * pCreatStrList();
int iPushStr(Node* head, char* str );
char * pPopStr(Node* head);
void vSortStr(Node* head); 
int iDeleteListStr(Node* head);

#endif
