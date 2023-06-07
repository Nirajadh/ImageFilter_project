
#include <stdio.h>   // standard input output header file
#include <conio.h>   // to use function such as getch and clrscr
#include <string.h>  // to use string function such as strcmp , strcpy, etc ..
#include <unistd.h>  // to use sleep function
#include <windows.h> // to make placement function


typedef struct Info
{
    char name[30];
    char password[30];
} Information;

void authentication_page();
void login();
void sign_up();
void exit_program();
void display_message();
void gotoxy(int x, int y); // this function might get replaced later
int x, y;
FILE *ptr;

int main()
{
    authentication_page();

    return 0;
}
void gotoxy(int x, int y)// user defined gotoxy function ... which change the coordinates of object 
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void authentication_page()
{
    system("cls");
    int choose_option;
    gotoxy(100,10);
    printf("IMAGE FILTER");
    gotoxy(100,15);
    printf("1.\tLogin");
      gotoxy(100,17);
    printf("2.\tNEW USER\n");
          gotoxy(100,19);
    printf("3.\tExit\n");
          gotoxy(100,21);
    printf("\t\tChoose Option");
    scanf("%d", &choose_option);
    switch (choose_option)
    {
    case 1:

        login();
        // printf("login page ");
        break;
    case 2:
        sign_up();
        // printf("signup page");
        break;
    case 3:
        exit_program();
        // printf("exit");

        break;
    default:
        printf("wrong input");
       system("cls");
authentication_page();
        break;
    }
}
void sign_up()
{
    system("cls");
    Information i;
    ptr = fopen("authentication.txt", "ab"); // opening file in binary mode
    gotoxy(100,10);
    printf("****** SignUp ******");   
    gotoxy(100,12);
    printf("Name :");
    scanf(" %[^\n]", i.name);
    fflush(stdin);
    gotoxy(100,14);
    printf("Password :");
    scanf(" %[^\n]", i.password);
    if (ptr == NULL)
    {
        printf("Unable to open file ");
    }
    else
    {
        fwrite(&i, sizeof(Information), 1, ptr); // writing into file in binary mode
         gotoxy(100,17);
        printf(" Signed Up Sucessfully !!");
        getch();
        fclose(ptr);
    }
    authentication_page();
}

void login()
{
    system("cls");

    // Open the authentication file in binary read mode
    ptr = fopen("authentication.txt", "rb");

    Information i;
    char enter_name[30];
    char enter_pass[30];
    int j;

  

    for (j = 1; j <= 5; j++)
    {
    	  gotoxy(100,10);
           printf("****** Login ******");
            gotoxy(100,12);
        printf("Attempt %d\n", j);
           gotoxy(100,14);
        printf("Name: ");
      
        scanf(" %[^\n]", enter_name);
        fflush(stdin);
         gotoxy(100,16);
        printf("Password: ");
        scanf(" %[^\n]", enter_pass);
        fflush(stdin);

        // Reset the file pointer to the beginning
        fseek(ptr, 0, SEEK_SET);

        // Read each struct from the file and compare the entered name and password
        while (fread(&i, sizeof(Information), 1, ptr))
        {
            // Check if the entered name and password match with the current struct
            if (strcmp(enter_name, i.name) == 0 && strcmp(enter_pass, i.password) == 0)
            {
            	 gotoxy(100,18);
                printf("Login Successful!\n");
                	 gotoxy(117,18);
                getch();
                fclose(ptr); // Close the file
                return;      // Exit the function
            }
        }

 
        // If no match is found, print login failure message
        Beep(600,600);
         gotoxy(100,20);
        printf("Invalid username or password. Please try again.\n");
        sleep(1);
        system("cls");
    }

    // If the loop finishes without successful login, display a message
     
    fclose(ptr); // Close the file
    display_message();
}

void exit_program()
{
system("cls");
gotoxy(80,20);
printf("Do you really Want To Exit ? y/n____");
char cha;
gotoxy(116,20);
cha=getchar();
if ( cha=='y' || cha=='Y')
{
    exit(1);
}
else if( cha=='n' || cha=='N'){
    authentication_page();
}
else{

    exit_program();
}



}
void display_message()
{
	gotoxy(90,20);
    printf("You entered Wrong Password for many times !!   ");
    gotoxy(90,22);
    printf("You might not have Signed Up your account Try signning up");
    gotoxy(90,24);
    printf(" Press any key__ ");
    gotoxy(107,24);
    getch();
    authentication_page();

}



