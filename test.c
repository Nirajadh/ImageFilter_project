# include<stdio.h>
# include <windows.h>
#include<string.h>
#include<conio.h>
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int main(){
    char a[100];

    gotoxy(10,10);
      printf("Enter Password"); 
      getch();
        gotoxy(10,10);
       printf("                  "); 
        gotoxy(10,10);
       scanf("%[^\n]",&a);
    return 0;
}