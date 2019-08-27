/*
UPDATE: 此任务已由 @bingogyz 完成，感谢他的贡献！我们正在审核并尝试将此函数融入源代码，请等待稍后告知！
如果您有比 @bingogyz 更好的实现方法，请提出Pull Request或在Issue中提出思路

代码说明：
login.cpp文件内容为VIP登录代码，头文件部分请自行补全
为防止用户信息泄露，我们将用户登录账号与密码的判定使用一个函数 getdata() 代替，请直接使用下面测试文件进行编译
任务：进行登录窗口美化，请使用WinAPI进行页面重构，并请保证能正确实现登录
请先Fork本项目，修改代码后再创建一个Pull Request，正式开发组成员将对其进行审核并讨论，也可能会Request Changes
开发组成员审查完毕后，会@code004Accepted进行复查，code004Accepted将把相关代码直接应用到GC Server的实际代码中进行测试
如果任务完成成功，将会成为正式开发组成员并会将用户名记录在新版本的关于窗口；如果滥用PR和Issue进行捣乱，将会考虑踢出开发组
GC Server开发组欢迎您的加入！
*/

#include<windows.h>
#include<conio.h>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
using namespace std;

bool namereg;
void closegraph(){return;}

HANDLE hInput;
INPUT_RECORD inRec;
DWORD numRead; 
HANDLE handle_in;  
HANDLE handle_out;  
CONSOLE_SCREEN_BUFFER_INFO csbi;
////////////////////////
//color
const int black=0;
const int darkblue=1;
const int darkgreen=2;
const int darklakeblue=3;
const int darkred=4;
const int purple=5;
const int darkyellow=6;
const int darkwhite=7;
const int grey=8;
const int blue=9;
const int green=10;
const int lakeblue=11;
const int red=12;
const int pink=13;
const int yellow=14;
const int white=15;

////////////////////////

struct pos{
    int x;
    int y;
};

////////////////////////
//This will set the position of the cursor
void gotoXY(int x, int y)
{
   //Initialize the coordinates
   COORD coord = {x, y};
   //Set the position
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//Hides the console cursor
void HideTheCursor()
{
   CONSOLE_CURSOR_INFO cciCursor;
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

   if(GetConsoleCursorInfo(hStdOut, &cciCursor))
   {
      cciCursor.bVisible = FALSE;
   }
}

void VSSetup(){
    handle_in = GetStdHandle(STD_INPUT_HANDLE); 
    handle_out = GetStdHandle(STD_OUTPUT_HANDLE); 
    INPUT_RECORD mouserec;
    DWORD res;
    COORD pos; 
    COORD size = {20, 25}; 
    GetConsoleScreenBufferInfo(handle_out, &csbi); 
    SetConsoleScreenBufferSize(handle_out, size); 
    HideTheCursor();
}

bool Mousepress(int x1,int x2,int y1,int y2){
    handle_in = GetStdHandle(STD_INPUT_HANDLE);
    handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    INPUT_RECORD mouserec; 
    DWORD res;
    COORD pos; 
    COORD size = {20, 25}; 
    GetConsoleScreenBufferInfo(handle_out, &csbi);
    SetConsoleScreenBufferSize(handle_out, size);
    ReadConsoleInput(handle_in, &mouserec, 1, &res);
    pos = mouserec.Event.MouseEvent.dwMousePosition;
    gotoXY(pos.X, pos.Y);  
    if (mouserec.EventType == MOUSE_EVENT)
        if (mouserec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) 
            if(pos.X<=x2&&pos.X>=x1&&pos.Y<=y2&&pos.Y>=y1)return true;
    return false;
}

void CursorSetup(){
    HWND hwnd=FindWindow("ConsoleWindowClass",NULL);
    hInput = GetStdHandle(STD_INPUT_HANDLE); 
}
void ClearScreen(void){
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    GetConsoleScreenBufferInfo( hOut, &bInfo );
    COORD home = {0, 0};
    WORD att = bInfo.wAttributes;
    unsigned long size = bInfo.dwSize.X * bInfo.dwSize.Y;
    FillConsoleOutputAttribute(hOut, att, size, home, NULL);
    FillConsoleOutputCharacter(hOut, ' ', size, home, NULL);
}

//This will clear the console while setting the forground and
//background colors.
void ClearConsoleToColors(int ForgC, int BackC)
{
   WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
   //Get the handle to the current output buffer...
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   //This is used to reset the carat/cursor to the top left.
   COORD coord = {0, 0};
   //A return value... indicating how many chars were written
   //not used but we need to capture this since it will be
   //written anyway (passing NULL causes an access violation).
   DWORD count;

   //This is a structure containing all of the console info
   // it is used here to find the size of the console.
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   //Here we will set the current color
   SetConsoleTextAttribute(hStdOut, wColor);
   if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
   {
      //This fills the buffer with a given character (in this case 32=space).
      FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

      FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
      //This will set our cursor position for the next print statement.
      SetConsoleCursorPosition(hStdOut, coord);
   }
}

//This will clear the console.
void ClearConsole()
{
   //Get the handle to the current output buffer...
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   //This is used to reset the carat/cursor to the top left.
   COORD coord = {0, 0};
   //A return value... indicating how many chars were written
   //   not used but we need to capture this since it will be
   //   written anyway (passing NULL causes an access violation).
   DWORD count;
   //This is a structure containing all of the console info
   // it is used here to find the size of the console.
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   //Here we will set the current color
   if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
   {
      //This fills the buffer with a given character (in this case 32=space).
      FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
      FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
      //This will set our cursor position for the next print statement.
      SetConsoleCursorPosition(hStdOut, coord);
   }
}

//This will set the forground color for printing in a console window.
void SetColor(int ForgC)
{
   WORD wColor;
   //We will need this handle to get the current background attribute
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   //We use csbi for the wAttributes word.
   if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
   {
      //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
   }
}

//This will set the forground and background color for printing in a console window.
void SetColorAndBackground(int ForgC, int BackC)
{
   WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

//Direct console output
void ConPrint(char *CharBuffer, int len)
{
   DWORD count;
   WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), CharBuffer, len, &count, NULL);
}

//Direct Console output at a particular coordinate.
void ConPrintAt(int x, int y, char *CharBuffer, int len)
{
   DWORD count;
   COORD coord = {x, y};
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   gotoXY(x,y);
   SetConsoleCursorPosition(hStdOut, coord);
   WriteConsole(hStdOut, CharBuffer, len, &count, NULL);
}

//Shows the console cursor
void ShowTheCursor()
{
   CONSOLE_CURSOR_INFO cciCursor;
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

   if(GetConsoleCursorInfo(hStdOut, &cciCursor))
   {
      cciCursor.bVisible = TRUE;
   }
}

void ChangeWinSize(int cols,int lines){
    char hs[100];
    sprintf(hs,"mode con cols=%d lines=%d",cols,lines);
    system(hs);
}

void login();
char username[1000]="";
char password[1000]="";

POINT Windowpos()
{
    POINT pt;
    GetCursorPos(&pt);
    HWND h=GetForegroundWindow();
    ScreenToClient(h,&pt);
    pt.x/=8;pt.y/=16;
    return pt; 
}

//0为没有反应
//1为悬浮
//2为点击
int mouse_detect(int x1,int x2,int y1,int y2){
    int mouse=GetAsyncKeyState(VK_LBUTTON)&0x8000;
    POINT pt=Windowpos();
    if(mouse){
        if(pt.x>=x1&&pt.x<=x2&&pt.y>=y1&&pt.y<=y2){
            return 2;
        }
    }
    else if(pt.x>=x1&&pt.x<=x2&&pt.y>=y1&&pt.y<=y2){
        return 1;
    }
    else{
        return 0;
    }
}
void display(char *p,int speed)
{
    for(int i=1;*p;i++){
        if(*p) printf("%c",*p++);
        Sleep(speed);
    }
}

int getdata(char username[],char password[])
{
    if(strcmp(username,"")==0){
        system("cls");
        SetColor(red);
        gotoXY(8,25);
        cout<<"请输入用户名";
        strcpy(password,"");
        return login();
    }
    if(strcmp(password,"")==0){
        system("cls");
        SetColor(red);
        gotoXY(8,25);
        cout<<"请输入密码";
        strcpy(username,"");
        return login();
    }
    return 1;
}

int login(){
    HideTheCursor();
    gotoXY(15,2);
    SetColor(white);
    display("GC Server - VIP login",10);

    gotoXY(26,3);
    SetColor(yellow);
    display("By Bingogyz",10);

    SetColor(white);
    gotoXY(4,7); display("┌────────────┬─────┐",0);
    gotoXY(4,8); display("│                        │          │",0);
    gotoXY(4,9); display("│      欢迎VIP！         │   By     │",0);
    gotoXY(4,10);display("│                        │          │",0);
    gotoXY(4,11);display("│ 用户名                 │Bingogyz  │",0);
    gotoXY(4,12);display("│ ┌────────┐   │          │",0);
    gotoXY(4,13);display("│ │                │   │          │",0);
    gotoXY(4,14);display("│ └────────┘   ├─────┤",0);
    gotoXY(4,15);display("│ 密码                   │加入我们? │",0);
    gotoXY(4,16);display("│ ┌────────┐   │          │",0);
    gotoXY(4,17);display("│ │                │   │┌───┐│",0);
    gotoXY(4,18);display("│ └────────┘   ││ 快   ││",0);
    gotoXY(4,19);display("│                        ││ 来   ││",0);
    gotoXY(4,20);display("│ ┌──┐    ┌──┐   ││ 点   ││",0);
    gotoXY(4,21);display("│ │登录│    │注册│   ││ 我   ││",0);
    gotoXY(4,22);display("│ └──┘    └──┘   │└───┘│",0);
    gotoXY(4,23);display("└────────────┴─────┘",0);


    while(1){
        HideTheCursor();
        while(!kbhit()){
            HideTheCursor();
            gotoXY(9,13);cout<<"               ";
            gotoXY(9,13);cout<<username;
            if(mouse_detect(7,15,20,22)==1){
                SetColor(darkwhite);
                gotoXY(7,20);printf("┌──┐");
                gotoXY(7,21);printf("│登录│");
                gotoXY(7,22);printf("└──┘");
            }
            else if(mouse_detect(7,15,20,22)==2){
                return getdata(username,password);
            }
            else {
                SetColor(white);
                gotoXY(7,20);printf("┌──┐");
                gotoXY(7,21);printf("│登录│");
                gotoXY(7,22);printf("└──┘");
            }

            if(mouse_detect(32,42,17,22)==1){
                SetColor(darkwhite);
                gotoXY(32,17);printf("┌───┐");
                gotoXY(32,18);printf("│ 快   │");
                gotoXY(32,19);printf("│ 来   │");
                gotoXY(32,20);printf("│ 点   │");
                gotoXY(32,21);printf("│ 我   │");
                gotoXY(32,22);printf("└───┘");
            }
            else if(mouse_detect(32,42,17,22)==2){
                system("start https://github.com/code004Accepted/GC-Server-dev");
                exit(0);
            }
            else {
                SetColor(white);
                gotoXY(32,17);printf("┌───┐");
                gotoXY(32,18);printf("│ 快   │");
                gotoXY(32,19);printf("│ 来   │");
                gotoXY(32,20);printf("│ 点   │");
                gotoXY(32,21);printf("│ 我   │");
                gotoXY(32,22);printf("└───┘");
            }

            if(mouse_detect(19,23,20,22)==1){
                SetColor(darkwhite);
                gotoXY(19,20);printf("┌──┐");
                gotoXY(19,21);printf("│注册│");
                gotoXY(19,22);printf("└──┘");
            }
            else if(mouse_detect(19,23,20,22)==2){
                SetColor(white);
                gotoXY(19,20);printf("注册账号");
                gotoXY(19,21);printf("请联系开");
                gotoXY(19,22);printf("发者人员");
            }
            else {
                SetColor(white);
                gotoXY(19,20);printf("┌──┐");
                gotoXY(19,21);printf("│注册│");
                gotoXY(19,22);printf("└──┘");
            }
        }
        HideTheCursor();
        char buf=getch();
        if(buf!=13)if(strlen(username)<15)sprintf(username,"%s%c",username,buf);else;
        else break; 
    }

    while(1){
        HideTheCursor();
        while(!kbhit()){
            HideTheCursor();
            gotoXY(9,17);cout<<"               ";
            gotoXY(9,17);for(int i=0;i<strlen(password);i++)cout<<'*';

            if(mouse_detect(7,15,20,22)==1){
                SetColor(darkwhite);
                gotoXY(7,20);printf("┌──┐");
                gotoXY(7,21);printf("│登录│");
                gotoXY(7,22);printf("└──┘");
            }
            else if(mouse_detect(7,15,20,22)==2){
                return getdata(username,password);
            }
            else {
                SetColor(white);
                gotoXY(7,20);printf("┌──┐");
                gotoXY(7,21);printf("│登录│");
                gotoXY(7,22);printf("└──┘");
            }

            if(mouse_detect(32,42,17,22)==1){
                SetColor(darkwhite);
                gotoXY(32,17);printf("┌───┐");
                gotoXY(32,18);printf("│ 快   │");
                gotoXY(32,19);printf("│ 来   │");
                gotoXY(32,20);printf("│ 点   │");
                gotoXY(32,21);printf("│ 我   │");
                gotoXY(32,22);printf("└───┘");
            }
            else if(mouse_detect(32,42,17,22)==2){
                system("start https://github.com/code004Accepted/GC-Server-dev");
                exit(0);
            }
            else {
                SetColor(white);
                gotoXY(32,17);printf("┌───┐");
                gotoXY(32,18);printf("│ 快   │");
                gotoXY(32,19);printf("│ 来   │");
                gotoXY(32,20);printf("│ 点   │");
                gotoXY(32,21);printf("│ 我   │");
                gotoXY(32,22);printf("└───┘");
            }

            if(mouse_detect(19,23,20,22)==1){
                SetColor(darkwhite);
                gotoXY(19,20);printf("┌──┐");
                gotoXY(19,21);printf("│注册│");
                gotoXY(19,22);printf("└──┘");
            }
            else if(mouse_detect(19,23,20,22)==2){
                SetColor(white);
                gotoXY(19,20);printf("注册账号");
                gotoXY(19,21);printf("请联系开");
                gotoXY(19,22);printf("发者人员");
            }
            else {
                SetColor(white);
                gotoXY(19,20);printf("┌──┐");
                gotoXY(19,21);printf("│注册│");
                gotoXY(19,22);printf("└──┘");
            }
        }
        HideTheCursor();
        char buf=getch();
        if(buf!=13) if(strlen(password)<15) sprintf(password,"%s%c",password,buf);else;
        else break; 
    }
    return getdata(username,password);
}
int main()
{
  printf("\n\n\t\tLogin Testing Program - GC Server Beta\n\n\t\tDevelopers Only\n");
  Sleep(1500);
  ChangeWinSize(50,30);
  HideTheCursor();
  login();
}
