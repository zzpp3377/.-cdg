#include "list.h"
#include <stdio.h>
int main(){
    Node* head;
    char* point;
    head=pCreateList();
    iPush(head,(void*)"hello");
    iPush(head,(void*)"i");
    iPush(head,(void*)"am");
    iPush(head,(void*)"zp");
    while( (point=(char*)pPop(head)) != NULL){
        printf("%s\n",point);
    }
    iAddLast(head,(void*)"who");
    iAddLast(head,(void*)"are");
    iAddLast(head,(void*)"you");
    while( (point=pPop(head))!=NULL ){
        printf("%s\n",point);
    }
    iDeleteList(head);
    return 0;
}
