#include <stdio.h>   // standard input output header file
#include <conio.h>   // to use function such as getch and clrscr // getch(); || _getch();
#include <string.h>  // to use string function such as strcmp , strcpy, etc ..
#include <unistd.h>  // to use sleep function
#include <windows.h> // to make placement function
#include <time.h>  
int arrow( int x, int y, int higc, int lowc, int pm);
void placementxy(int x, int y) ;


void placementxy(int x, int y) // user defined gotoxy function ... which change the coordinates of object
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main(){
    arrow(1,1,1,5,1);
    return 0;
}
int arrow( int x, int y, int higc, int lowc, int pm) // arrow  function
{
    int hig = 1;
    int low = 0;
    
    int ch;
p:
    fflush(stdin);
    ch = getch();
    if (ch == 0 || ch == 224)
    {

        while (ch != 13)
        {
            if (ch == 27)
            {

                return 0;
            }
            if (y == higc )
            {
                hig = 1;
            }
            else
            {
                hig = 0;
            }

            if (y == lowc )
            {
                low = 1;
            }
            else
            {
                low = 0;
            }
              placementxy(x,y);
            printf("\033[1;31m");
                printf("\033[44m");
             printf("->");
            
            printf("\033[0m");
           
            ch = getch();
            switch (ch)
            {
            case 72: // up
                
                    if (hig != 1)
                    {
                        placementxy(x,y);
                         printf("  ");
                        y=y-pm;
                    }
                
                break;
            case 80: // down
               
                    if (low != 1)
                    {
                        placementxy(x,y);
                         printf("  ");
                       y=y+pm;
                    }
                
                break;
           
            default:

                break;
            }
        }
    }
    else if (ch == 27)
    {

        return 0;
    }
    else
    {
        goto p;
    }
   
    return y;
}