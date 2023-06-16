 Information in[4];
    info = fopen("authentication.txt", "ab+");
         fread(in, sizeof(Information)*4, 1, info);
 
    char pass[30];
    login(in[userno]);
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

    scanf("%[^\n]", pass);
