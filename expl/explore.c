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


//char cContentDir[100][100]={0,0};
int iContentDir=0;
//char cContentFile[100][100]={0};
int iContentFile=0;

Node * pDirHead;
Node * pFileHead;

WINDOW * wndNewWindow=NULL;

int iCursesX=0;
int iCursesY=0;

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
 
    while((deCurrentDirEnt = readdir( dirCurrentDir )) != NULL){
        
        lstat(deCurrentDirEnt->d_name , &statbuffer);
        if( 
            S_ISDIR( statbuffer.st_mode ) ){
//            sprintf( cContentDir[iContentDir] , "%s" , deCurrentDirEnt->d_name);
            iPushStr(pDirHead,deCurrentDirEnt->d_name);
            iContentDir++;
        }else {
//            sprintf( cContentFile[iContentFile] , "%s" , deCurrentDirEnt->d_name);
            iPushStr(pFileHead,deCurrentDirEnt->d_name);
            iContentFile++;
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
    point =pDirHead;
    while(point->next!=NULL){
        point=point->next;
        mvprintw(i,0,"%s/",(char*)point->pContent);
        i++;
    }
    point =pFileHead;
    while(point->next!=NULL){
        point=point->next;
        mvprintw(i,0,"%s",(char*)point->pContent);
        i++;
    }
    
    move(0,0);
    iCursesY = 0;
    iCursesX = 0;
    refresh();
}

//------------------------------------------------------
//function :vInitNewWindow
//-----------------------------------------------------
void vInit(){
    initscr();
    keypad(stdscr,true);
    noecho();

    pDirHead=pCreateList();
    pFileHead=pCreateList();
}

//----------------------------------------------------
//function : vEndWindow
//---------------------------------------------------
void vEnd(){
    while(!iIsEmptyStr(pDirHead))pPopStr(pDirHead);
    while(!iIsEmptyStr(pFileHead))pPopStr(pFileHead);
    iDeleteListStr(pDirHead); 
    iDeleteListStr(pFileHead);

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
                if( iCursesY-1 >=0 ) move( --iCursesY , iCursesX );break;
            case KEY_DOWN :
                if( iCursesY+1 < (iContentDir+iContentFile) ) move( ++iCursesY , iCursesX );break;
            case KEY_LEFT :
                if( iCursesX-1 >=0 ) move( iCursesY , --iCursesX );break;
            case KEY_RIGHT :
                move( iCursesY , ++iCursesX );break;
        }
        refresh();
    }
}
//---------------------------------------------------
//function : vOutPut
//--------------------------------------------------
void vOutPut(){
    int i=0;
    Node * point=NULL;
    char * home=getenv("HOME");
    chdir(home);
    int file = open("tempexplore",O_WRONLY|O_CREAT,S_IWUSR|S_IREAD);
    if(iCursesY<iContentDir){
        for(i=0,point=pDirHead->next;i<iCursesY;i++){
            point=point->next;
        }
        write(file,"d\n",2);
        write(file,(char*)point->pContent,strlen((char*)point->pContent));
        write(file,"\n",1);
    }else{ 
        for(i=0,point=pFileHead->next;i<iCursesY-iContentDir;i++){
            point=point->next;
        }
        write(file,"f\n",2);
        write(file,(char*)point->pContent,strlen((char*)point->pContent));
        write(file,"\n",1);
        
    }
    close(file);
    file=-1;
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
    vGetContent(dirCurrentDir);
    closedir(dirCurrentDir);
    vSortStr(pDirHead);
    vSortStr(pFileHead);
    vShowContent();
   

    vMainLoop();
    vOutPut();
    vEnd();
    exit(0);
}








