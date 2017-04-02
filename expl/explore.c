#include "stdlib.h"
#include "dirent.h"
#include "unistd.h"
#include "string.h"
#include "sys/types.h"
#include "stdio.h"
#include "sys/stat.h"
#include "ncurses.h"
#include "fcntl.h"
#include "strList.h"
#include "termios.h"
#include "sys/ioctl.h"

char *error[]={
    "please entry your path!\n",
    "can not find your path!\n"
};

struct explore{
    int iContentDir;
    int iContentFile;
    int iCursesX;
    int iCursesY;
    int iShellTop;
    int iShellBottom;
    int iShellRight;
    Node * pDirHead;
    Node * pFileHead;
    char path[100];
};

struct explore explr;

WINDOW * wndNewWindow=NULL;


//------------------------------------------------------
//function: vGetWinSize
//input:int * col,int* row    ///input!=NULL
//------------------------------------------------------
void vGetWinSize(struct explore * pexplr){
    struct winsize size;
    ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
    pexplr->iShellRight =size.ws_col;
    pexplr->iShellBottom =size.ws_row;
    pexplr->iShellTop=0;
}

//-----------------------------------------------------------
//function : vGetContent()
//----------------------------------------------------------
void vGetContent(DIR * dirCurrentDir){
    
    struct dirent * deCurrentDirEnt=NULL;
    struct stat statbuffer;
    explr.iContentDir=0;
    explr.iContentFile=0;
    while((deCurrentDirEnt = readdir( dirCurrentDir )) != NULL){
        
        lstat(deCurrentDirEnt->d_name , &statbuffer);
        if( S_ISDIR( statbuffer.st_mode ) ){
            iPushStr(explr.pDirHead,deCurrentDirEnt->d_name);
            explr.iContentDir++;
        }else {
            iPushStr(explr.pFileHead,deCurrentDirEnt->d_name);
            explr.iContentFile++;
        }
    }
}

//----------------------------------------------------------
//function : vShowContent()
//---------------------------------------------------------
void vShowContent(){
    int j=0;
    int col,row;
    Node* point;
    point =explr.pDirHead;
    clear();

    for( j=0; j<explr.iShellTop ;j++ ){
        if( j==explr.iContentDir ){
            point=explr.pFileHead->next;
        }
        point=point->next;
    }
    if( j<explr.iContentDir ){
        while(point->next!=NULL&&j<explr.iShellBottom){
            point=point->next;
            mvprintw( j-explr.iShellTop,0,"%s/",(char*)point->pContent );
            j++;
        }
        point =explr.pFileHead;
        while(point->next!=NULL&&j<explr.iShellBottom){
            point=point->next;
            mvprintw( j-explr.iShellTop,0,"%s",(char*)point->pContent );
            j++;
        }
    }else{ 
        while(point->next!=NULL&&j<explr.iShellBottom){
            point=point->next;
            mvprintw( j-explr.iShellTop,0,"%s",(char*)point->pContent );
            j++;
        }
    }
//    move(0,0);
//    explr.iCursesY = 0;
//    explr.iCursesX = 0;
    refresh();
}

//------------------------------------------------------
//function :vInitNewWindow
//-----------------------------------------------------
void vInit(){
    initscr();
    keypad(stdscr,true);
    noecho();

    explr.pDirHead=pCreateList();
    explr.pFileHead=pCreateList();
}

//----------------------------------------------------
//function : vEndWindow
//---------------------------------------------------
void vEnd(){
    iDeleteListStr(explr.pDirHead); 
    iDeleteListStr(explr.pFileHead);

    endwin();
}
//-------------------------------------------------
//function : vMainLoop()
//-------------------------------------------------
void vMainLoop(){
    int key = 0;
    while( (key=getch()) != 'q'){
        
        if(key == '\n')break;
        
        switch( key ){
            case KEY_UP  :
                if( explr.iCursesY-1 >=0  ) move( --explr.iCursesY , explr.iCursesX );
                else if( explr.iShellTop >0 ) {
                    explr.iShellTop--;
                    explr.iShellBottom--;
                    vShowContent();
                    move( explr.iCursesY , explr.iCursesX );
                }
                break;
            case KEY_DOWN :
                if( explr.iCursesY+1 < explr.iShellBottom-explr.iShellTop ) move( ++explr.iCursesY , explr.iCursesX );
                else if( explr.iShellBottom < explr.iContentDir+explr.iContentFile ){
                    explr.iShellTop++;
                    explr.iShellBottom++;
                    vShowContent();
                    move( explr.iCursesY , explr.iCursesX );
                }
                break;
            case KEY_LEFT :
                if( explr.iCursesX-1 >=0 ) move( explr.iCursesY , --explr.iCursesX );break;
            case KEY_RIGHT :
                if(explr.iCursesX<explr.iShellRight)move( explr.iCursesY , ++explr.iCursesX );break;
        }
        refresh();
    }
}
//---------------------------------------------------
//function : vOutPut
//--------------------------------------------------
void vOutPut(){
    char * home=getenv("HOME");
    if( getcwd(explr.path,100)==NULL ) exit(1);
    chdir(home);
    int file = open("tempexplore",O_WRONLY|O_CREAT,S_IWUSR|S_IREAD);
    write(file,explr.path,strlen(explr.path));
    write(file,"\n",1);
    close(file);
    file=-1;
}
//-----------------------------------------------------
//function : iChDir()
//output: int flag //0----选择了“.” , 1----选择了非"."
//----------------------------------------------------
int iChDir(){
    int i=0;
    Node *point;
    if( explr.iCursesY+explr.iShellTop < explr.iContentDir ){
        for( i=0,point=explr.pDirHead->next;i<explr.iCursesY+explr.iShellTop;i++ ){
            point=point->next;
        }
        chdir(point->pContent);
    }else{ 
            //////选中文件，而不是目录时进行的操作
    }
    if(strcasecmp(point->pContent,".")==0)return 0;
    else return 1;
}
//-------------------------------------------------------
//function : main()
//-------------------------------------------------------
int main(int argc,char *argv[]){

    DIR * dirCurrentDir=NULL;

    if((dirCurrentDir=opendir("."))==NULL){
        write(2,error[1],strlen(error[1]));
        exit(1);
    }

    vInit();
    vGetWinSize(&explr);
    while(1){
        dirCurrentDir=opendir(".");
        vGetContent(dirCurrentDir);
        closedir(dirCurrentDir);
        vSortStr(explr.pDirHead);
        vSortStr(explr.pFileHead);
        vGetWinSize(&explr);
        vShowContent();
        move(0,0);
        explr.iCursesY=0;
        explr.iCursesX=0;
        vMainLoop();

        if(iChDir()==0)break;
        while(!iIsEmptyStr(explr.pDirHead))pPopStr(explr.pDirHead);
        while(!iIsEmptyStr(explr.pFileHead))pPopStr(explr.pFileHead);
    }
    vOutPut();
    vEnd();
    exit(0);
}








