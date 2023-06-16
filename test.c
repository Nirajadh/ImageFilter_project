# include<stdio.h>
# include <windows.h>
#include<string.h>
#include<conio.h>
FILE * fp;
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int main(){
char a[200]="adhikari";
char b[100]="niraj";
strcpy(a,b);
printf("%s",a);
    return 0;
}