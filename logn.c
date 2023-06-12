
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
FILE *info;
typedef struct Info
{
    char username[30];
    char password[30];
} Information;

int userslog();
int newuser();
int exitprg();
void rect(int xa, int xb, int ya, int yb);
void gotoxy(int x, int y);
int first();

int main()
{
    first();
    return 0;
}
void rect(int xa, int xb, int ya, int yb)
{
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
}
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int first()
{
    system("cls");
    rect(20, 102, 4, 25); // border
    fflush(stdin);
    int choose_option = 0;
    gotoxy(54, 6);
    printf("IMAGE FILTER");
    rect(49, 70, 10, 12);
    gotoxy(50, 11);
    printf("1.  SELECT USER");
    rect(49, 70, 13, 15);
    gotoxy(50, 14);
    printf("2.  NEW USER\n");
    rect(49, 70, 16, 18);
    gotoxy(50, 17);
    printf("3.  GUEST USER\n");
    rect(49, 70, 19, 21);
    gotoxy(50, 20);
    printf(" \t Exit");

    gotoxy(50, 23);
    printf("    Choose Option");
    scanf("%d", &choose_option);

    switch (choose_option)
    {
    case 1:

        userslog();

        break;
    case 2:
        newuser();

        break;
    case 3:
        exitprg();

        break;
    default:
        printf("wrong input");
        system("cls");
        first();
        break;
    }
    return 0;
}

int newuser()
{
    system("cls");
    rect(38, 90, 4, 21);
    Information i;
    info = fopen("authentication.txt", "ab"); // opening file in binary mode
    gotoxy(58, 5);
    printf(" Sign up ");
    rect(38, 90, 6, 6);
    rect(49, 80, 11, 13);
    rect(49, 80, 8, 10);
    gotoxy(50, 9);
    printf("Name :");
    scanf(" %[^\n]", i.username);
    fflush(stdin);
    gotoxy(50, 12);
    printf("Password :");

    scanf(" %[^\n]", i.password);
    if (info == NULL)
    {
        printf("Unable to open file ");
    }
    else
    {
        fwrite(&i, sizeof(Information), 1, info); // writing into file in binary mode
        gotoxy(50, 17);
        printf(" Signed Up Sucessfully !!");
        getch();
        fclose(info);
    }
    first();

    return 0;
}
int userslog()
{
    int c = 9, d = 11, f = 10 , choose_option=0;
    Information in[5];
    system("cls");
    rect(20, 102, 4, 25);
    rect(44, 78, 7, 23);
    gotoxy(58, 5);
    printf("USERS");

    info = fopen("authentication.txt", "r");
    int i = 0;
    while (fread(&in[i], sizeof(Information), 1, info))
    {
        rect(49, 72, c, d);
        gotoxy(51, f);
        printf("%d. %s", i+1, in[i].username);
        c = c + 3;
        d = d + 3;
        f = f + 3;
        i++;
    }

        gotoxy(50, 23);
    printf("    Choose Option");
    scanf("%d", &choose_option);

    switch (choose_option)
    {
    case 1:
       system("cls");
rect(20, 102, 4, 25);
    rect(44, 78, 7, 23);
  rect(49, 72, 9, 11);
  gotoxy(54, 10);
  printf("%s",in[0].username);
        break;
    case 2:
        system("cls");
     rect(20, 102, 4, 25);
    rect(44, 78, 7, 23);
rect(49, 72, 9, 11);
  gotoxy(54, 10);
  printf("%s",in[1].username);
        break;
    case 3:
        system("cls");
rect(20, 102, 4, 25);
    rect(44, 78, 7, 23);
rect(49, 72, 9, 11);
  gotoxy(54, 10);
  printf("%s",in[2].username);
        break;
    default:
        printf("wrong input");
        system("cls");
        userslog();
        break;
    }
    return 0;
}

int exitprg()
{
    return 0;
}