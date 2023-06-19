
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h> //sleep
#include <windows.h>
#include <stdlib.h>
#include <stdint.h>
#include <dirent.h>
#include <time.h>
char infile[100];
char password[24];
#pragma pack(push, 1)
typedef struct
{
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset; // uint vaneko unsingned int ho (positive value matra huncha)
    uint32_t dib_header_size;
    int32_t width_px;
    int32_t height_px;
    uint16_t num_planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size_bytes;
    int32_t x_resolution_ppm;
    int32_t y_resolution_ppm;
    uint32_t num_colors;
    uint32_t important_colors;
} BMPHeader;
typedef struct
{
    uint8_t rgbtBlue;
    uint8_t rgbtGreen;
    uint8_t rgbtRed;
} pixel;
#pragma pack(pop)
void listf(char *path);
int searchimg(char *openpath);
int dirdis(int m);
void grayscale(int height, int width, pixel image[height][width]);
void sepia(int height, int width, pixel image[height][width]);
void red(int height, int width, pixel image[height][width]);
void blue(int height, int width, pixel image[height][width]);
int Filter();

FILE *info;
int userno;
int nusers;
char img_name[30];
int i = 9, x = 31;
int count = 1;
char username[30];
FILE *userfile;
typedef struct Info
{
    char username[30];
    char password[30];
} Information;

typedef struct act
{
    time_t xtime;
    char inpfile[50];
    char outfile[50];

} details;

void saveNUsers();
void loadNUsers();
void userslog();
void login(Information x, int cp);
void guest();
void newuser();
void exitprg();
void delete();
void change_pass();
void options(Information x);
void rect(int xa, int xb, int ya, int yb);
void gotoxy(int x, int y);
void first();
void select_img();
void select_filter();
void home();
void pass();
void cursor(int x);
int check(char uname[30]);
int main()
{

    loadNUsers();
    first();
    return 0;
}

int check(char uname[30])
{
    Information in[4];
    info = fopen("authentication.txt", "r");
    for (int i = 0; i < nusers; i++)
    {
        fread(&in[i], sizeof(Information), 1, info);
        if (strcmp(in[i].username, uname) == 0)
        {
            return 1;
        }
    }
    fclose(info);
    return 0;
}
void cursor(int x)
{

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    if (x == 1)
    {
        cursorInfo.bVisible = TRUE;
    }
    else
    {
        cursorInfo.bVisible = FALSE;
    }

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void rect(int xa, int xb, int ya, int yb)
{

    printf("\033[1m");
    int i = 0;
    for (i = xa; i < xb; i++)
    {
        gotoxy(i, ya);
        printf("%c", 205);
        gotoxy(i, yb);
        printf("%c", 205);
    }

    // Drawing all the corner of the rectangle
    gotoxy(xa - 1, ya);
    printf("%c", 201);
    gotoxy(xb, ya);
    printf("%c", 187);
    gotoxy(xa - 1, yb);
    printf("%c", 200);
    gotoxy(xb, yb);
    printf("%c", 188);

    // Drawing vertical line
    for (i = ya + 1; i < yb; i++)
    {
        gotoxy(xa - 1, i);
        printf("%c", 186);
        gotoxy(xb, i);
        printf("%c", 186);
    }
    printf("\033[0m");
}
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void first()
{
    int c = 10, d = 12;
    int hig = 1, low = 0;
    system("cls");

    rect(20, 102, 4, 25); // border
    fflush(stdin);
    // int choose_option = 0;
    gotoxy(54, 6);
    printf("\033[1m"); // bold
    printf("\033[4m"); // underline
    printf("IMAGE FILTER");
    printf("\033[0m");
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
        // printf("    Choose Option");
        // scanf("%d", &choose_option);
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

        // gotoxy(53, 23);
        // printf("Choose Option");
        // scanf("%d", &choose_option);
    }
    cursor(0);
    int ch;
p:
    fflush(stdin);
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

            if (c == 19 && d == 21)
            {
                low = 1;
            }
            else
            {
                low = 0;
            }
        }
    }
    else
    {
        goto p;
    }
    if (ch == 13)
    {
        cursor(1);
    }
    switch (c)
    {
    case 10:

        userslog();

        break;
    case 13:
        if (nusers < 4)
        {
            newuser();
        }
        else
        {
            guest();
        }

        break;
    case 16:
        if (nusers < 4)
        {
            guest();
        }
        else
        {
            exitprg();
        }

        break;
    case 19:
        if (nusers < 4)
        {
            exitprg();
        }

        break;
    default:
        // gotoxy(54, 24);
        //     printf("wrong input");
        //      gotoxy(66, 23);
        //     printf("     ");
        //     sleep(2);
        system("cls");
        first();
        break;
    }
}
void newuser()
{
    system("cls");
    rect(38, 90, 4, 21);
    Information i;

    gotoxy(58, 5);
    printf(" Sign up ");
    rect(38, 90, 6, 6);
    rect(49, 80, 11, 13);
    rect(49, 80, 8, 10);
    gotoxy(50, 9);
    printf("Name :");
    scanf(" %[^\n]", i.username);
    if (check(i.username) == 1)
    {
        gotoxy(56, 9);
        printf("Username already exists!");
        cursor(0);
        Sleep(1200);
        cursor(1);
        newuser();
    }

    fflush(stdin);
    gotoxy(50, 12);
    printf("Password :");

    pass();
    strcpy(i.password, password);
    info = fopen("authentication.txt", "ab"); // opening file in binary mode
    if (info == NULL)
    {
        printf("Unable to open file ");
        sleep(1);
    }
    else
    {

        fwrite(&i, sizeof(Information), 1, info); // writing into file in binary mode
        gotoxy(50, 17);
        printf(" Signed Up Sucessfully !!");
        sleep(1);
        nusers++;
        saveNUsers();
        fclose(info);
    }
    first();
}
void userslog()
{
    int c = 9, d = 11, f = 10;
    Information in[4];
    system("cls");

    rect(20, 102, 4, 25);
    rect(44, 78, 7, 23);
    printf("\033[1m"); // bold
    printf("\033[4m");
    
        gotoxy(58, 5);
    printf("USERS");
    printf("\033[0m");
        gotoxy(22, 5);
    printf("%c", 174);
    info = fopen("authentication.txt", "r");

    for (int i = 0; i < nusers; i++)
    {
        fread(&in[i], sizeof(Information), 1, info);
        rect(49, 72, c, d);
        gotoxy(51, f);
        printf("%d. %s", i + 1, in[i].username);
        c = c + 3;
        d = d + 3;
        f = f + 3;
    }
    fclose(info);
    c = 9;
    d = 11;
    int hc = 6 + (nusers * 3);
    int hd = 8 + (nusers * 3);
    int hig = 1, low = 0;
    cursor(0);
    int ch;
m:
    fflush(stdin);
    ch = getch();
    if (ch == 0 || ch == 224)
    {
        while (ch != 13)
        {
            if (c == 9 && d == 11)
            {
                hig = 1;
            }
            else
            {
                hig = 0;
            }

            if (c == hc && d == hd)
            {
                low = 1;
            }
            else
            {
                low = 0;
            }
            printf("\033[1;31m");
            rect(49, 72, c, d);
            printf("\033[0m");
            ch = getch();
            if (ch == 27)
            {
                printf("\033[1;31m");
                gotoxy(22, 5);
                printf("%c", 174);
                printf("\033[0m");
                Sleep(1000);
                first();
            }
            switch (ch)
            {
            case 72: // up
                if (hig != 1)
                {
                    rect(49, 72, c, d);
                    c = c - 3;
                    d = d - 3;
                }

                break;
            case 80: // down
                if (low != 1)
                {
                    rect(49, 72, c, d);
                    c = c + 3;
                    d = d + 3;
                }

                break;
            default:

                break;
            }
        }
    }
    else if (ch == 27)
    {
        printf("\033[1;31m");
        gotoxy(22, 5);
        printf("%c", 174);
        printf("\033[0m");
        Sleep(1000);
        first();
    }
    else
    {
        goto m;
    }
    if (ch == 13)
    {
        cursor(1);
    }
    switch (c)
    {

    case 9:
        if (nusers >= 1)
        {
            userno = 0;
            options(in[0]);
            break;
        }

        goto xxy;
    case 12:
        if (nusers >= 2)
        {
            userno = 1;
            options(in[1]);
            break;
        }

        goto xxy;
    case 15:
        if (nusers >= 3)
        {
            userno = 2;
            options(in[2]);
            break;
        }
        goto xxy;

    case 18:
        if (nusers == 4)
        {
            userno = 3;
            options(in[3]);
            break;
        }

        goto xxy;

    case 0:
        first();

        break;
    default:

    xxy:
        break;
    }
    first();
}
void guest()
{
    system("cls");
    rect(38, 90, 4, 21);
    gotoxy(50, 17);
    printf(" Logged in as Guest !!");
    sleep(2);
}
void exitprg()
{
    exit(0);
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
void login(Information x, int cp)
{

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
    Sleep(1200);
xxx:
    fflush(stdin);

    gotoxy(53, 13);
    printf("              ");
    gotoxy(53, 13);
    pass();

    if (strcmp(password, x.password) == 0)
    {
        gotoxy(50, 15);
        printf("Logged in succesfully");
        Sleep(1200);

        userfile = fopen(strcat(x.username, ".txt"), "ab");
        fclose(userfile);
        fflush(stdin);
        if (cp == 0)
        {
            home();
        }
    }
    else
    {
        gotoxy(51, 15);
        printf("Incorrect Password");
        sleep(2);
        fflush(stdin);
        gotoxy(51, 15);
        printf("                  ");
        goto xxx;
    }
}
void options(Information x)
{
    strcpy(username, x.username);

    system("cls");
    gotoxy(45, 7);
    printf("%s", x.username);
    rect(40, 90, 6, 18);
    rect(47, 55, 10, 13);

    gotoxy(41, 7);
    printf("%c", 174);
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

    int c = 47;
    int d = 55;
    int hig = 1, low = 0;
    cursor(0);
    int ch;
m:
    fflush(stdin);
    ch = getch();
    if (ch == 0 || ch == 224)
    {
        while (ch != 13)
        {
            if (c == 47 && d == 55)
            {
                hig = 1;
            }
            else
            {
                hig = 0;
            }

            if (c == 75 && d == 83)
            {
                low = 1;
            }
            else
            {
                low = 0;
            }
            if (ch == 27)
            {
                printf("\033[1;31m");
                gotoxy(41, 7);
                printf("%c", 174);
                printf("\033[0m");
                Sleep(1000);
                userslog();
            }
            printf("\033[1;31m");
            rect(c, d, 10, 13);
            printf("\033[0m");
            ch = getch();

            switch (ch)
            {
            case 75: // left
                if (hig != 1)
                {
                    rect(c, d, 10, 13);
                    c = c - 14;
                    d = d - 14;
                }

                break;
            case 77: // right
                if (low != 1)
                {
                    rect(c, d, 10, 13);
                    c = c + 14;
                    d = d + 14;
                }

                break;
            default:

                break;
            }
        }
    }
    else if (ch == 27)
    {
        printf("\033[1;31m");
        gotoxy(41, 7);
        printf("%c", 174);
        printf("\033[0m");
        Sleep(1000);
        userslog();
    }

    else
    {
        goto m;
    }
    if (ch == 13)
    {
        cursor(1);
    }
    switch (c)
    {
    case 47:
        login(x, 0);
        break;
    case 61:
        change_pass(x);
        break;
    case 75:
        delete (x);
        break;
    case 0:
        userslog();
        break;
    }
}
void delete()
{
    Information in[4];
    system("cls");
    rect(40, 80, 12, 19);
    gotoxy(45, 14);
    printf("Are you sure you want to delete");
    gotoxy(55, 15);
    printf("this user?");
    rect(42, 47, 16, 18);
    rect(74, 78, 16, 18);
    gotoxy(43, 17);
    printf("Yes");
    gotoxy(75, 17);
    printf("No");
    int choose_option;
xxx:
    fflush(stdin);
    gotoxy(50, 20);
    printf("Choose Option");
    gotoxy(64, 20);
    scanf("%d", &choose_option);

    switch (choose_option)
    {
    case 1:

        info = fopen("authentication.txt", "rb");
        for (int i = 0; i < nusers; i++)
        {
            fread(&in[i], sizeof(Information), 1, info);
        }

        for (int i = userno; i < nusers; i++)
        {
            if (i == nusers - 1)
            {
                strcpy(in[nusers - 1].password, "");
                strcpy(in[nusers - 1].username, "");
            }
            else
            {
                strcpy(in[i].password, in[i + 1].password);
                strcpy(in[i].username, in[i + 1].username);
            }
        }

        fclose(info);
        nusers--;
        saveNUsers(nusers);
        info = fopen("authentication.txt", "wb");
        for (int i = 0; i < nusers; i++)
        {
            fwrite(&in[i], sizeof(Information), 1, info);
        }

        fclose(info);
        system("cls");
        gotoxy(55, 15);
        printf("User Deleted..");
        Sleep(1400);
        userslog();
        break;
    case 2:
        strcpy(in[userno].username, username);
        options(in[userno]);

        break;
    default:
        gotoxy(64, 20);
        printf("     ");
        goto xxx;
        break;
    }
}
void change_pass()
{
    Information in[4];

    getch();
    info = fopen("authentication.txt", "rb");
    for (int i = 0; i < nusers; i++)
    {
        fread(&in[i], sizeof(Information), 1, info);
    }
    fclose(info);
    printf("%s", in[userno].password);
    login(in[userno], 1);

    system("cls");
    rect(44, 78, 7, 20);
    rect(49, 72, 9, 11);
    gotoxy(54, 10);
    printf("%s", in[userno].username);
    rect(49, 72, 12, 14);
    gotoxy(53, 13);
    printf("New Password");
    Sleep(1200);
    fflush(stdin);
    /////////////////////////
    gotoxy(53, 13);
    printf("              ");
    gotoxy(53, 13);

    pass();
    strcpy(in[userno].password, password);
    info = fopen("authentication.txt", "wb");
    for (int i = 0; i < nusers; i++)
    {
        fwrite(&in[i], sizeof(Information), 1, info);
    }

    fclose(info);
}

void select_filter()
{

    system("cls");
    rect(20, 102, 4, 25);
    rect(30, 92, 7, 22);
    printf("\033[1m");
    printf("\033[4m");
    gotoxy(58, 5);
    printf("FILTERS");
    printf("\033[0m");
    fflush(stdin);

    gotoxy(21, 5);
    printf("%c", 174);
    rect(32, 45, 9, 13);
    gotoxy(34, 11);
    printf("Grayscale");
    rect(47, 60, 9, 13);
    gotoxy(51, 11);
    printf("Sepia");
    rect(62, 75, 9, 13);
    gotoxy(67, 11);
    printf("red");
    rect(77, 90, 9, 13);
    gotoxy(81, 11);
    printf("blue");
}
void home()
{

    system("cls");
    rect(20, 102, 4, 25); // border
    printf("\033[1m");
    printf("\033[4m");
    gotoxy(21, 5);
    printf("%s", username);
    printf("\033[0m");

    rect(27, 41, 11, 17);
    gotoxy(29, 14);
    printf("ADD FILTER");

    rect(45, 59, 11, 17);
    gotoxy(46, 14);
    printf("DELETE IMAGE");

    rect(63, 77, 11, 17);
    gotoxy(66, 14);
    printf("HISTORY");

    rect(81, 95, 11, 17);
    gotoxy(85, 14);
    printf("LOGOUT");
    int c = 27;
    int d = 41;
    int hig = 1, low = 0;
    cursor(0);
    int ch;
m:
    fflush(stdin);
    ch = getch();
    if (ch == 0 || ch == 224)
    {
        while (ch != 13)
        {
            if (c == 27 && d == 41)
            {
                hig = 1;
            }
            else
            {
                hig = 0;
            }

            if (c == 81 && d == 95)
            {
                low = 1;
            }
            else
            {
                low = 0;
            }
            if (ch == 27)
            {
                printf("\033[1;31m");
                gotoxy(41, 7);
                printf("%c", 174);
                printf("\033[0m");
                Sleep(1000);
                userslog();
            }
            printf("\033[1;31m");
            rect(c, d, 11, 17);
            printf("\033[0m");
            ch = getch();

            switch (ch)
            {
            case 75: // left
                if (hig != 1)
                {
                    rect(c, d, 11, 17);
                    c = c - 18;
                    d = d - 18;
                }

                break;
            case 77: // right
                if (low != 1)
                {
                    rect(c, d, 11, 17);
                    c = c + 18;
                    d = d + 18;
                }

                break;
            default:

                break;
            }
        }
    }
    else if (ch == 27)
    {
        printf("\033[1;31m");
        gotoxy(41, 7);
        printf("%c", 174);
        printf("\033[0m");
        Sleep(1000);
        userslog();
    }

    else
    {
        goto m;
    }
    if (ch == 13)
    {
        cursor(1);
    }

    switch (c)
    {
    case 27:
        dirdis(0);
        Filter();
        home();
        break;
    case 45:
        dirdis(1);
        remove(infile);
        system("cls");
        printf("Image Deleted.");
        Sleep(1200);
        home();
        break;
    case 63:

        break;
    case 81:
        first();
        break;
    }
}

int Filter()
{
    system("cls");
    char out[100] = {"C:\\Users\\Niraj adh\\Pictures\\"};
    strcat(img_name, "_N.bmp");
    strcat(out, img_name);

    select_filter();

    int c = 32;
    int d = 45;
    int hig = 1, low = 0;
    cursor(0);
    int ch;
m:
    fflush(stdin);
    ch = getch();
    if (ch == 0 || ch == 224)
    {
        while (ch != 13)
        {
            if (c == 32 && d == 45)
            {
                hig = 1;
            }
            else
            {
                hig = 0;
            }

            if (c == 77 && d == 90)
            {
                low = 1;
            }
            else
            {
                low = 0;
            }
            if (ch == 27)
            {
                printf("\033[1;31m");
                gotoxy(21, 5);
                printf("%c", 174);
                printf("\033[0m");
                Sleep(1000);
                dirdis(0);
            }
            printf("\033[1;31m");
            rect(c, d, 9, 13);
            printf("\033[0m");
            ch = getch();

            switch (ch)
            {
            case 75: // left
                if (hig != 1)
                {
                    rect(c, d, 9, 13);
                    c = c - 15;
                    d = d - 15;
                }

                break;
            case 77: // right
                if (low != 1)
                {
                    rect(c, d, 9, 13);
                    c = c + 15;
                    d = d + 15;
                }

                break;
            }
        }
    }
    else if (ch == 27)
    {
        printf("\033[1;31m");
        gotoxy(21, 5);
        printf("%c", 174);
        printf("\033[0m");
        Sleep(1000);
        dirdis(0);
    }

    else
    {
        goto m;
    }
    if (ch == 13)
    {
        cursor(1);
    }
    FILE *inputf = fopen(infile, "rb");

    if (inputf == NULL)
    {
        fclose(inputf);
        printf("\nCould not open input img");
        return 0;
    }
    FILE *outf = fopen(out, "wb");
    if (inputf == NULL)
    {
        fclose(inputf);
        printf("\nCould not open output img");
        return 0;
    }

    BMPHeader header;

    fread(&header, sizeof(BMPHeader), 1, inputf);
    int height = abs(header.height_px);
    int width = header.width_px;

    fwrite(&header, sizeof(BMPHeader), 1, outf);
    pixel(*image)[width] = calloc(height, width * sizeof(pixel)); // image ko 2d array bancha ra calloc use garera memory allocate gareko.
    if (image == NULL)
    {
        printf("Not enough memory to store image.\n");
        fclose(outf);
        fclose(inputf);
        return 7;
    }
    int padding = (4 - (width * sizeof(pixel)) % 4) % 4;

    // input file bata data read garera array ma store gareko
    for (int i = 0; i < height; i++)
    {

        fread(image[i], sizeof(pixel), width, inputf);
    }

    switch (c)
    {
    case 32:

        grayscale(height, width, image);
        break;
    case 47:

        sepia(height, width, image);
        break;
    case 62:

        red(height, width, image);
        break;
    case 77:

        blue(height, width, image);
        break;
    }

    // write data to output file
    for (int i = 0; i < height; i++)
    {
        fwrite(image[i], sizeof(pixel), width, outf);
        for (int j = 0; j < padding; j++)
        {
            fputc(0x00, outf);
        }
    }
    system("cls");
    gotoxy(51, 11);
    printf("Filter Applied");

    free(image);
    fclose(inputf);
    fclose(outf);

    char a[50] = {"\""};
    char b[50] = {"rere"};
    strcpy(b, a);
    strcat(b, out);
    strcat(b, a);
    system(b);

    Sleep(1200);
    home();
    return 0;
}

int dirdis(int m)
{
    char *deskpath = {"C:\\Users\\Niraj adh\\desktop"};
    char *picpath = {"C:\\Users\\Niraj adh\\Pictures"};
    char *downpath = {"C:\\Users\\Niraj adh\\Downloads"};
    char openpath[200];
    system("cls");
    rect(20, 102, 4, 25);
    rect(30, 92, 7, 22);
    printf("\033[1m");
    printf("\033[4m");
    gotoxy(58, 5);
    printf("Images");
    printf("\033[0m");
    fflush(stdin);
    listf(deskpath);
    listf(picpath);
    listf(downpath);
    i = 9;
    x = 31;
    count = 1;
    char image[100];
    gotoxy(43, 20);
    printf("SEARCH IMAGE :");
    gotoxy(58, 20);
    fgets(image, sizeof(image), stdin);
    image[strcspn(image, "\n")] = '\0';
    strcpy(img_name, image);
    img_name[strcspn(img_name, ".")] = '\0';
    strcpy(openpath, picpath);
    strcat(openpath, "\\");
    strcat(openpath, image);
    int ch = searchimg(openpath);
    if (ch == 1)
    {
        strcpy(openpath, deskpath);
        strcat(openpath, "\\");
        strcat(openpath, image);
        ch = searchimg(openpath);
        if (ch == 1)
        {
            strcpy(openpath, downpath);
            strcat(openpath, "\\");
            strcat(openpath, image);
            ch = searchimg(openpath);
            if (ch == 1)
            {
                printf("Failed to open the file.\n");
                Sleep(1200);
                dirdis(0);
                return 1;
            }
        }
    }

    strcpy(infile, openpath);
    if (m == 0)
    {
        char a[50] = {"\""};
        char b[50] = {"rere"};
        strcpy(b, a);
        strcat(b, openpath);
        strcat(b, a);
        system(b);
        Filter();
    }
    return 0;
}

int searchimg(char *openpath)
{

    FILE *file;
    file = fopen(openpath, "r");

    if (file == NULL)
    {
        return 1;
    }

    else
    {
        puts(openpath);
        // File opened successfully, you can perform further operations on it here.
        printf("File opened successfully!\n");
        // Close the file
        fclose(file);
        return 0;
    }
}

void listf(char *path)
{

    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            char *ext = strrchr(dir->d_name, '.');
            if (ext != NULL && strcmp(ext, ".bmp") == 0)
            {
                if (i >= 19)
                {
                    i = 9;
                    x = 50;
                }

                gotoxy(x, i);
                printf("%d.%s\n", count, dir->d_name);
                i = i + 2;
                count++;
            }
        }
        closedir(d);
        return;
    }
}

// filter functions
void grayscale(int height, int width, pixel image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;
            int avg = (blue + green + red) / 3;

            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
}
void sepia(int height, int width, pixel image[height][width])
{
}
void red(int height, int width, pixel image[height][width])
{
}
void blue(int height, int width, pixel image[height][width])
{
}

void pass()
{

    char ch;
    int i = 0;
    while ((ch = getch()) != 13)
    {
        if (ch == 8)
        {
            if (i > 0)
            {
                printf("\b \b");
                i--;
            }
        }
        else if (ch < 33)
        {
        }

        else if (i < 24)
        {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
}
