#include <stdio.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
#include <conio.h>
void rect(int xa, int xb, int ya, int yb);
void gotoxy(int x, int y);
int main()
{
    int c = 10, d = 12;
    int hig = 1, low = 0;
    system("cls");
    rect(20, 102, 4, 25);
    printf("\033[1m");
    gotoxy(54, 6);
    printf("\033[1m");
    printf("\033[4m");
    printf("IMAGE FILTER");
    printf("\033[0m");
    rect(49, 70, 10, 12);
    gotoxy(50, 11);
    printf("1.  SELECT USER");
    rect(49, 70, 13, 15);
    gotoxy(50, 14);
    printf("2.  GUEST USER\n");
    rect(49, 70, 16, 18);
    gotoxy(50, 17);
    printf(" \t Exit");
    int ch;
    ch = getch();
    if (ch == 0 || ch == 224)
    {
        while (ch != 13)
        {

            printf("\033[1;31m");
            rect(49, 70, c, d);
            printf("\033[0m");
            ch = getch();

            switch (ch)
            {
            case 72: // up
                if (hig != 1)
                {
                    rect(49, 70, c, d);
                    c = c - 3;
                    d = d - 3;
                }

                break;
            case 80: // down
                if (low != 1)
                {
                    rect(49, 70, c, d);
                    c = c + 3;
                    d = d + 3;
                }

                break;
            default:

                break;
            }
            if (c == 10 && d == 12)
            {
                hig = 1;
            }
            else
            {
                hig = 0;
            }

            if (c == 16 && d == 18)
            {
                low = 1;
            }
            else
            {
                low = 0;
            }
        }
    }
}
    void gotoxy(int x, int y)
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    void rect(int xa, int xb, int ya, int yb)
    {

        printf("\033[1m");
        int i = 0;
        for (i = xa; i < xb; i++)
        {
            gotoxy(i, ya);
            printf("%c", 196);
            gotoxy(i, yb);
            printf("%c", 196);
        }

        // Drawing all the corner of the rectangle
        gotoxy(xa - 1, ya);
        printf("%c", 218);
        gotoxy(xb, ya);
        printf("%c", 191);
        gotoxy(xa - 1, yb);
        printf("%c", 192);
        gotoxy(xb, yb);
        printf("%c", 217);

        // Drawing vertical line
        for (i = ya + 1; i < yb; i++)
        {
            gotoxy(xa - 1, i);
            printf("%c", 179);
            gotoxy(xb, i);
            printf("%c", 179);
        }
        printf("\033[0m");
    }
