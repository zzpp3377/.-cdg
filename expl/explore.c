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
    Node * pDirHead;
    Node * pFileHead;
    char path[100];
};

struct explore explr;

WINDOW * wndNewWindow=NULL;


//------------------------------------------------------
//function: pGetWinSize
//input:int * col,int* row    ///input!=NULL
//------------------------------------------------------
void pGetWinSize(int * col,int *row){
    struct winsize size;
    ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
    *col=size.ws_col;
    *row=size.ws_row;
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
    int i=0;
    int col,row;
    Node* point;
    point =explr.pDirHead;
    clear();
    while(point->next!=NULL){
        point=point->next;
        mvprintw(i,0,"%s/",(char*)point->pContent);
        i++;
    }
    point =explr.pFileHead;
    while(point->next!=NULL){
        point=point->next;
        mvprintw(i,0,"%s",(char*)point->pContent);
        i++;
    }
    
    move(0,0);
    explr.iCursesY = 0;
    explr.iCursesX = 0;
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
//    while(!iIsEmptyStr(explr.pDirHead))pPopStr(explr.pDirHead);
//    while(!iIsEmptyStr(explr.pFileHead))pPopStr(explr.pFileHead);
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
                if( explr.iCursesY-1 >=0 ) move( --explr.iCursesY , explr.iCursesX );break;
            case KEY_DOWN :
                if( explr.iCursesY+1 < (explr.iContentDir+explr.iContentFile) ) move( ++explr.iCursesY , explr.iCursesX );break;
            case KEY_LEFT :
                if( explr.iCursesX-1 >=0 ) move( explr.iCursesY , --explr.iCursesX );break;
            case KEY_RIGHT :
                move( explr.iCursesY , ++explr.iCursesX );break;
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
//-----------------------------------------------------
int iChDir(){
    int i=0;
    Node *point;
    if( explr.iCursesY < explr.iContentDir ){
        for(i=0,point=explr.pDirHead->next;i<explr.iCursesY;i++){
            point=point->next;
        }
        chdir(point->pContent);
    }else{ 
//        for(i=0,point=explr.pFileHead->next;i<explr.iCursesY-explr.iContentDir;i++){
//            point=point->next;
//        }
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
    while(1){
        dirCurrentDir=opendir(".");
        vGetContent(dirCurrentDir);
        closedir(dirCurrentDir);
        vSortStr(explr.pDirHead);
        vSortStr(explr.pFileHead);
        vShowContent();
        vMainLoop();

        if(iChDir()==0)break;
        while(!iIsEmptyStr(explr.pDirHead))pPopStr(explr.pDirHead);
        while(!iIsEmptyStr(explr.pFileHead))pPopStr(explr.pFileHead);
    }
    vOutPut();
    vEnd();
    exit(0);
}








