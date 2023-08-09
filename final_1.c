
#include <stdio.h>
#include <conio.h>
#include <string.h>  //string funtions
#include <unistd.h>  //sleep
#include <windows.h> //placement
#include <time.h>    //time functions
#include <stdlib.h>  //malloc,calloc
#include <stdint.h>  //unsigned integers
#include <dirent.h>  //directory
typedef struct
{
    char image_name[30];
} images;

images im[15];
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

typedef struct
{
    char inpfile[30];
    char outfile[30];
    char Filter[30];
    char date[30];

} details;

void saveNUsers();
void loadNUsers();
void userslog();
int login(Information x, int cp);
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
void history();
int check(char uname[30]);
int arrow(int mode, int a, int b, int c, int d, int higc, int lowc, int pm);

char deskpath[200] = {"C:\\Users\\"};
char picpath[200] = {"C:\\Users\\"};
char downpath[200] = {"C:\\Users\\"};

int main() // no. of users load -- get pc ko username -- path haru -- first call
{

    loadNUsers();

    char *user_name = getenv("USERNAME");

    strcat(deskpath, user_name);
    strcat(deskpath, "\\desktop");

    strcat(picpath, user_name);
    strcat(picpath, "\\Pictures");

    strcat(downpath, user_name);
    strcat(downpath, "\\Downloads");

    first();
    return 0;
}

int check(char uname[30]) // username already exists xa ki nai check garni
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
void cursor(int x) // cursor show/hide garni {1== show , 0 ==hide}
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
void rect(int xa, int xb, int ya, int yb) // rectangle banauni (UI)
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
void gotoxy(int x, int y) // placement
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void first() // First page - { newusers, users , exit , guest }
{
    int c = 10, d = 12;

    int n = 0, low = 19;
    system("cls");

    rect(20, 102, 4, 25); // border
    fflush(stdin);
    // int choose_option = 0;
    gotoxy(55, 6);
    printf("\033[1m"); // bold
    printf("\033[4m"); // underline
    printf("IMAGE FILTER");
    printf("\033[0m");
    rect(50, 71, 10, 12);
    gotoxy(55, 11);
    printf("SELECT USER");
    if (nusers >= 4)
    {
        rect(50, 71, 13, 15);
        gotoxy(55, 14);
        printf("GUEST USER");
        rect(50, 71, 16, 18);
        gotoxy(58, 17);
        printf("Exit");
        n = 1;
        gotoxy(49, 20);
    }
    else
    {
        rect(50, 71, 13, 15);
        gotoxy(56, 14);
        printf("NEW USER");
        rect(50, 71, 16, 18);
        gotoxy(55, 17);
        printf("GUEST USER");
        rect(50, 71, 19, 21);

        gotoxy(58, 20);
        printf("Exit");
    }

    if (n == 1)
    {
        low = 16;
    }
    switch (arrow(0, 50, 71, c, d, 10, low, 3))
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

        system("cls");
        first();
        break;
    }
}
void newuser() // new user create garni
{
    system("cls");
    rect(38, 90, 4, 21);
    Information i;
  int ch;

    gotoxy(58, 5);
    printf(" Sign up ");
    rect(38, 90, 6, 6);
    rect(49, 80, 11, 13);
    rect(49, 80, 8, 10);
  
    
    gotoxy(50, 9);
    printf("Name :");
        ch=getch();
if (ch==27)
{
     cursor(0);
    printf("\033[1;31m");
    gotoxy(39, 5);
    printf("%c", 174);
    printf("\033[0m");
    Sleep(1000);
    first();
}
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
 ch=getch();
if (ch==27)
{
 
    printf("\033[1;31m");
    gotoxy(39, 5);
    printf("%c", 174);
    printf("\033[0m");
    Sleep(1000);
    first();
       cursor(1);
}
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
void userslog() // user select garni
{
    if (nusers != 0)
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

        switch (arrow(0, 49, 72, c, d, 9, hc, 3))
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
            printf("\033[1;31m");
            gotoxy(22, 5);
            printf("%c", 174);
            printf("\033[0m");
            Sleep(1000);

            first();

            break;
        default:

        xxy:
            break;
        }
    }
    first();
}
void guest() // guest user
{
    system("cls");
    rect(38, 90, 4, 21);
    gotoxy(50, 12);
    printf(" Logged in as Guest !!");
    sleep(1);
    strcpy(username, "GUEST");
    home();
}
void exitprg() // exit program
{
    exit(0);
}
void saveNUsers() // Number of users file ma save garni
{
    FILE *file = fopen("nusers.txt", "w");
    if (file != NULL)
    {
        fprintf(file, "%d", nusers);
        fclose(file);
    }
}
void loadNUsers() // program run vayesi no. of users load garni

{
    FILE *file = fopen("nusers.txt", "r");
    if (file != NULL)
    {
        fscanf(file, "%d", &nusers);
        fclose(file);
    }
}
int login(Information x, int cp) // login page
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
    else if (password[0] == 27)
    {
        printf("\033[1;31m");
        gotoxy(21, 5);
        printf("%c", 174);
        printf("\033[0m");
        Sleep(1000);
        return 1;
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
    return 0;
}
void options(Information x) // user options {login , delete , change password}
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
    switch (arrow(1, c, d, 10, 13, 47, 75, 14))
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
        printf("\033[1;31m");
        gotoxy(41, 7);
        printf("%c", 174);
        printf("\033[0m");
        Sleep(1000);
        userslog();
        break;
    }
    options(x);
}
void delete() // delete user
{
    Information in[4];
    system("cls");
    rect(40, 80, 12, 19);
    gotoxy(45, 14);
    printf("Are you sure you want to delete");
    gotoxy(55, 15);
    printf("this user?");
    rect(42, 47, 16, 18);
    rect(73, 78, 16, 18);
    gotoxy(43, 17);
    printf("Yes");
    gotoxy(75, 17);
    printf("No");
    switch (arrow(1, 42, 47, 16, 18, 42, 73, 31))
    {
    case 42:

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
        char deluser[50];
        strcpy(deluser, username);
        strcat(deluser, ".txt");
        remove(deluser);

        system("cls");
        gotoxy(55, 15);
        printf("User Deleted..");
        Sleep(1400);
        userslog();
        break;
    case 73:
        strcpy(in[userno].username, username);
        options(in[userno]);

        break;
    }
}
void change_pass() // change password
{
    Information in[4];
    info = fopen("authentication.txt", "rb");
    for (int i = 0; i < nusers; i++)
    {
        fread(&in[i], sizeof(Information), 1, info);
    }
    fclose(info);
    printf("%s", in[userno].password);
    if (login(in[userno], 1) == 1)
    {
        return;
    }

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
    if (password[0] == 27)
    {
        printf("\033[1;31m");
        gotoxy(45, 8);
        printf("%c", 174);
        printf("\033[0m");
        Sleep(1000);
        return;
    }
    strcpy(in[userno].password, password);
    info = fopen("authentication.txt", "wb");
    for (int i = 0; i < nusers; i++)
    {
        fwrite(&in[i], sizeof(Information), 1, info);
    }

    fclose(info);
}

void select_filter() // filter ko ui
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
    gotoxy(65, 11);
    printf("Color++");
    rect(77, 90, 9, 13);
    gotoxy(81, 11);
    printf("blue");
}
void home() // login garesi home
{
xxx:
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

    switch (arrow(1, c, d, 11, 17, 27, 81, 18))
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
        history();
        break;
    case 81:
        first();
    default:
        goto xxx;
        break;
    }
}

int Filter() // filter apply garni
{
    system("cls");

    char out[100];
    strcpy(out, picpath);
    char inpimg[30];
    char filter[30];
    strcat(out, "//");
    strcpy(inpimg, img_name);
  
    strcat(out, inpimg);
  strcat(out, "_n.bmp");
    select_filter();

    int c = 32;
    int d = 45;
    int arr = arrow(1, c, d, 9, 13, 32, 77, 15);
    if (arr == 0)
    {
        printf("\033[1;31m");
        gotoxy(21, 5);
        printf("%c", 174);
        printf("\033[0m");
        Sleep(1000);
        dirdis(0);
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

    switch (arr)
    {
    case 32:
        strcpy(filter, "grayscale");
        grayscale(height, width, image);
        break;
    case 47:
        strcpy(filter, "sepia");
        sepia(height, width, image);
        break;
    case 62:
        strcpy(filter, "color++");
        red(height, width, image);
        break;
    case 77:
        strcpy(filter, "blue");
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
          system("cls");
    rect(40, 80, 12, 19);
    gotoxy(44, 14);
    printf("Do you want to save this Image ?");
   
    rect(42, 47, 16, 18);
    rect(73, 78, 16, 18);
    gotoxy(43, 17);
    printf("Yes");
    gotoxy(75, 17);
    printf("No");
    switch (arrow(1, 42, 47, 16, 18, 42, 73, 31))
    {
    case 42:
        break;
    case 73:
        remove(b);
       Filter();
       return 0;
        break;
    }


    char usertxt[30];
    char tempimgname[30];
    strcpy(tempimgname,inpimg);
    strcpy(usertxt, username);
    userfile = fopen(strcat(usertxt, ".txt"), "ab");
    details de;
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    strftime(de.date, sizeof(de.date), "%d %b, %I:%M %p", localTime);
    strcpy(de.inpfile, strcat(tempimgname, ".bmp"));
    
    strcpy(de.outfile, strcat(inpimg, "_n.bmp"));
 
  
    strcpy(de.Filter, filter);
    fwrite(&de, sizeof(details), 1, userfile);
    fclose(userfile);
    Sleep(1200);
    home();
    return 0;
}

int dirdis(int m) // directory bata image select garni
{

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
    int cho, chp;
    gotoxy(43, 20);
    printf("SELECT IMAGE :");
    gotoxy(58, 20);
    int i = 0;
    fflush(stdin);
    while ((cho = getch()) != 13)
    {
        if (cho == 27)
        {

            cursor(0);
            printf("\033[1;31m");
            gotoxy(21, 5);
            printf("%c", 174);
            printf("\033[0m");
            Sleep(1000);
            home();
            cursor(1);
        }
        else if (cho == 8)
        {
            if (i > 0)
            {

                printf("\b \b");
                i--;
            }
        }
        else if (cho < 33)
        {
        }

        else if (i < 22)
        {
            chp = cho - 48;
            printf("%c", cho);
            i++;
        }
    }

    printf("\n%d", chp);
    strcpy(image, im[chp - 1].image_name);
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

int searchimg(char *openpath) // image search garni
{

    FILE *file;
    file = fopen(openpath, "r");

    if (file == NULL)
    {
        return 1;
    }

    else
    {
        //  gotoxy(43, 21);
        // puts(openpath);
        gotoxy(43, 23);
        printf("File opened successfully!");
        Sleep(1000);
        // Close the file
        fclose(file);
        return 0;
    }
}

void listf(char *path) // bmp image haru print garni..
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
                strcpy(im[(count - 1)].image_name, dir->d_name);
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
void grayscale(int height, int width, pixel image[height][width]) //
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
void sepia(int height, int width, pixel image[height][width]) //
{
    float red, blue, green;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;
            red = image[i][j].rgbtRed;

            float sb = 0.272 * red + 0.534 * green + 0.131 * blue;
            float sr = 0.393 * red + 0.769 * green + 0.189 * blue;
            float sg = 0.349 * red + 0.686 * green + 0.168 * blue;
            if (sb > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sb;
            }
            if (sr > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sr;
            }
            if (sg > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sg;
            }
        }
    }
}
void red(int height, int width, pixel image[height][width]) //
{
    int blue, red, green;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blue = image[i][j].rgbtBlue;
            red = image[i][j].rgbtRed;
            green = image[i][j].rgbtGreen;
            if (red <= 235 && blue < 235 && green < 235)
            {

                if (blue > red && blue > green)
                {
                    image[i][j].rgbtBlue = image[i][j].rgbtBlue + 20;
                }
                if (red > blue && red > green)
                {
                    image[i][j].rgbtRed = image[i][j].rgbtRed + 20;
                }
                if (green > blue && green > red)
                {
                    image[i][j].rgbtGreen = image[i][j].rgbtGreen + 20;
                }
            }
        }
    }
}
void blue(int height, int width, pixel image[height][width]) //
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (image[i][j].rgbtBlue < 205)
            {

                image[i][j].rgbtBlue = image[i][j].rgbtBlue + 50;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }
        }
    }
}

void pass() // password hidden mode ma lini
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
        else if (ch < 33 && ch != 27)
        {
        }
        else if (ch == 27)
        {
            password[0] = ch;
            password[1] = '\0';
            return;
        }
        else if (i < 24)
        {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
}

void history() // history display garni
{
    system("cls");

    gotoxy(25, 5);
    printf("Input File");
    gotoxy(48, 5);
    printf("FILTER");
    gotoxy(64, 5);
    printf("Output File");
    gotoxy(92, 5);
    printf("Date");
    char usertxt[30];
    strcpy(usertxt, username);
    userfile = fopen(strcat(usertxt, ".txt"), "rb");
    details n;
    rect(20, 102, 6, 6);
    int a = 7;
    int i = 1;
    while (fread(&n, sizeof(details), 1, userfile) == 1)
    {

        gotoxy(21, a);
        printf("%d.", i);
        gotoxy(25, a);
        printf("%s", n.inpfile);
        gotoxy(48, a);
        printf("%s", n.Filter);
        gotoxy(65, a);
        printf("%s", n.outfile);
        gotoxy(85, a);
        printf("%s", n.date);

        a = a + 3;
        i++;
    }
    rect(20, 102, 4, a + 2);
    fclose(userfile);
    getch();
    home();
}

int arrow(int mode, int a, int b, int c, int d, int higc, int lowc, int pm) // arrow  function
{
    int hig = 1;
    int low = 0;
    cursor(0);
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
            if (c == higc || a == higc)
            {
                hig = 1;
            }
            else
            {
                hig = 0;
            }

            if (c == lowc || a == lowc)
            {
                low = 1;
            }
            else
            {
                low = 0;
            }
            printf("\033[1;31m");
            rect(a, b, c, d);
            printf("\033[0m");
            ch = getch();

            switch (ch)
            {
            case 72: // up
                if (mode == 0)
                {
                    if (hig != 1)
                    {
                        rect(a, b, c, d);
                        c = c - pm;
                        d = d - pm;
                    }
                }
                break;
            case 80: // down
                if (mode == 0)
                {
                    if (low != 1)
                    {
                        rect(a, b, c, d);
                        c = c + pm;
                        d = d + pm;
                    }
                }
                break;
            case 75: // left
                if (mode == 1)
                {
                    if (hig != 1)
                    {
                        rect(a, b, c, d);
                        a = a - pm;
                        b = b - pm;
                    }
                }
                break;
            case 77: // right
                if (mode == 1)
                {
                    if (low != 1)
                    {
                        rect(a, b, c, d);
                        a = a + pm;
                        b = b + pm;
                    }
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
    if (ch == 13)
    {
        cursor(1);
    }
    if (mode == 1)
    {
        return a;
    }

    return c;
}