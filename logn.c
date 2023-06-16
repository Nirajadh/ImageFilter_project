
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>
FILE *info;
int userno;
FILE *userfile;
typedef struct Info
{
    char username[30];
    char password[30];
} Information;
void saveNUsers();
void loadNUsers();
int userslog();
int login(Information x);
int guest();
int newuser();
int exitprg();
void delete(Information x);
void change_pass();
int options(Information x);
void rect(int xa, int xb, int ya, int yb);
void gotoxy(int x, int y);
int first();

int nusers;
int main()
{
    loadNUsers();
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
    if (nusers >= 4)
    {
        rect(49, 70, 13, 15);
        gotoxy(50, 14);
        printf("2.  GUEST USER\n");
        rect(49, 70, 16, 18);
        gotoxy(50, 17);
        printf(" \t Exit");

        gotoxy(49, 20);
        printf("    Choose Option");
        scanf("%d", &choose_option);
    }
    else
    {
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
    }

    switch (choose_option)
    {
    case 1:

        userslog();

        break;
    case 2:
        if (nusers < 4)
        {
            newuser();
        }
        else
        {
            guest();
        }

        break;
    case 3:
        if (nusers < 4)
        {
            guest();
        }
        else
        {
            exitprg();
        }

        break;
    case 4:
        if (nusers < 4)
        {
            exitprg();
        }

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
        nusers++;
        saveNUsers();
        getch();
        fclose(info);
    }
    first();

    return 0;
}
int userslog()
{
    int c = 9, d = 11, f = 10, choose_option = 0;
    Information in[4];
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
        printf("%d. %s", i + 1, in[i].username);
        c = c + 3;
        d = d + 3;
        f = f + 3;
        i++;
    }
xxx:
    fflush(stdin);
    gotoxy(54, 22);
    printf("Choose Option");
    gotoxy(68, 22);
    scanf("%d", &choose_option);

    switch (choose_option)
    {
    case 1:
     userno = 0;
        options(in[0]);
       
        break;
    case 2:
     userno = 1;
        options(in[1]);
       
        break;
    case 3:
      userno = 2;
        options(in[2]);
      
        break;
    case 4:
     userno = 3;
        options(in[3]);
       
        break;
    default:
        gotoxy(55, 24);
        printf("wrong input");
        gotoxy(68, 22);
        printf("     ");
        goto xxx;
        break;
    }
    return 0;
}
int guest()
{
    system("cls");
    rect(38, 90, 4, 21);
    gotoxy(50, 17);
    printf(" Logged in as Guest !!");
    return 0;
}
int exitprg()
{
    return 0;
}
void saveNUsers()
{
    FILE *file = fopen("nusers.txt", "w");
    if (file != NULL)
    {
        fprintf(file, "%d", nusers);
        fclose(file);
    }
}
void loadNUsers()

{
    FILE *file = fopen("nusers.txt", "r");
    if (file != NULL)
    {
        fscanf(file, "%d", &nusers);
        fclose(file);
    }
}
int login(Information x)
{
    char pass[30];
    system("cls");
    rect(20, 102, 4, 25);
    gotoxy(58, 6);
    printf("LOGIN");
    rect(44, 78, 7, 20);
    rect(49, 72, 9, 11);
    gotoxy(54, 10);
    printf("%s", x.username);
    rect(49, 72, 12, 14);
    gotoxy(53, 13);
    printf("Enter Password");
    getch();
xxx:
    fflush(stdin);
    /////////////////////////
    gotoxy(53, 13);
    printf("              ");
    gotoxy(53, 13);

    scanf("%[^\n]", pass);

    if (strcmp(pass, x.password) == 0)
    {
        gotoxy(50, 15);
        printf("Logged in succesfully");
        userfile = fopen(strcat(x.username, ".txt"), "ab");
        fclose(userfile);
        fflush(stdin);
        getch();
    }
    else
    {
        gotoxy(51, 15);
        printf("Incorrect Password");
        getch();
        gotoxy(51, 15);
        printf("                  ");
        goto xxx;
    }

    return 0;
}
int options(Information x)
{
    int choose_option;
    system("cls");
    gotoxy(41, 7);
    printf("%s", x.username);
    rect(40, 90, 6, 18);
    rect(48, 55, 10, 13);
    gotoxy(49, 11);
    printf("Login");
    rect(61, 69, 10, 13);
    gotoxy(62, 11);
    printf("Change");
    gotoxy(61, 12);
    printf("Password");
    rect(75, 83, 10, 13);
    gotoxy(76, 11);
    printf("Delete");
xxx:
    fflush(stdin);
    gotoxy(57, 16);
    printf("Choose Option");
    gotoxy(71, 16);
    scanf("%d", &choose_option);

    switch (choose_option)
    {
    case 1:
        login(x);
        break;
    case 2:
        change_pass(x);
        break;
    case 3:
        delete (x);
        break;
    default:
        gotoxy(71, 16);
        printf("     ");
        goto xxx;
        break;
    }
    return 0;
}
void delete(Information x)
{
}
void change_pass()
{
    Information in[4];
    printf("%d", userno);
    getch();
    info = fopen("authentication.txt", "rb");
    for (int i = 0; i < 4; i++)
    {
      fread(&in[i], sizeof(Information), 1, info);  
    }
  fclose(info);
  printf("%s",in[userno].password);
   login(in[userno]);
    char pass[30];

    system("cls");
    rect(44, 78, 7, 20);
    rect(49, 72, 9, 11);
    gotoxy(54, 10);
    printf("%s", in[userno].username);
    rect(49, 72, 12, 14);
    gotoxy(53, 13);
    printf("New Password");
    getch();
    fflush(stdin);
    /////////////////////////
    gotoxy(53, 13);
    printf("              ");
    gotoxy(53, 13);

    scanf(" %[^\n]", pass);
    strcpy(in[userno].password, pass);
    info = fopen("authentication.txt", "wb");
for (int  i = 0; i < 4; i++)
{
 fwrite(&in[i], sizeof(Information), 1, info);
}

   
    fclose(info);

}