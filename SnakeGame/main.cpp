#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <iomanip>
using namespace std;

const int width = 20, height = 20;
int headx,heady, fruitx, fruity, bodyx, bodyy;
bool gameOver = true;
int score = 0;
int tailSz;
int tailx[width]={0}, taily[height]={0};

enum direction{STOP=0, LEFT, RIGHT, UP, DOWN};
direction dir = STOP;
void Setup(){
    gameOver = false;
    headx = width/2;
    heady = height/2;
    fruitx = rand() % width;
    fruity = rand() % height;
    tailSz =0;
};

void Draw(){
    system("cls");
    for(int i = 0; i<width;i++)
        cout<<setw(2)<<"#";
    cout<<"   SCORE: "<<score;
    cout<<endl;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(j==0)
                cout<<"#";
            if(j==headx&&i==heady)
                cout<<setw(2)<<"O";
            else if(j==fruitx&&i==fruity)
                cout<<setw(2)<<"F";
            else{
                bool print = false;
                for(int k=0;k<tailSz;k++){
                    if(j==tailx[k]&&i==taily[k]){
                        cout<<setw(2)<<"o";
                        print = true;
                    }
                }
                if(print==false)
                    cout<<setw(2)<<" ";
            }

            if(j==width-1)
                cout<<"#";
        }
        cout<<endl;
    }
    for(int i = 0; i<width;i++)
        cout<<setw(2)<<"#";


};

void Input(){

    if(kbhit()){
        switch(getch()){
        case 'a':
            dir=LEFT;
            break;
        case 's':
            dir=DOWN;
            break;
        case 'w':
            dir=UP;
            break;
        case 'd':
            dir=RIGHT;
            break;
        case 27:
            gameOver=true;
            break;
        }
    }
};

void Logic(){
    int prevX = tailx[0];
    int prevY = taily[0];
    int prev2X,prev2Y;
    tailx[0] = headx;
    taily[0] = heady;
    for(int i=1;i<tailSz;i++){
        prev2X=tailx[i];
        prev2Y=taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }


    switch(dir){
    case LEFT:
        headx--;
        break;
    case RIGHT:
        headx++;
        break;
    case UP:
        heady--;
        break;
    case DOWN:
        heady++;
        break;
    }
    if(headx<0)
        headx++;
    if(headx>width-1)
        headx--;
    if(heady<0)
        heady++;
    if(heady>height-1){
        heady--;
    }

    for(int i=0;i<tailSz;i++){
        if(headx==tailx[i]&&heady==taily[i]){
            gameOver=true;
            break;
        }
    }

    if(headx==fruitx&&heady==fruity){
        fruitx = rand() % width;
        fruity = rand() % height;
        score+=10;
        tailSz++;
    }
};

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursoInfo;
    CursoInfo.dwSize = 1;         /* The size of caret */
    CursoInfo.bVisible = false;   /* Caret is visible? */
    SetConsoleCursorInfo(hConsole, &CursoInfo);


    Setup();
    while(!gameOver){
        Draw();
        Input();
        Logic();
        Sleep(40);
    }
    if(gameOver){
        system("cls");
        cout<<"GAME OVER"<<endl;
        cout<<"SCORE: "<<score<<endl;
    }

    return 0;
}
