#include <stdio.h>
#include <dirent.h>
#include <string.h>

//{
void listf(char *path);
int searchimg(char *openpath);
void dirdis();
//}

//{
int main()
{
dirdis();

    return 0;
}
//}



// functions



void dirdis(){
    char *deskpath = {"C:\\Users\\Niraj adh\\desktop"};
    char *picpath = {"C:\\Users\\Niraj adh\\Pictures"};
    char *downpath ={"C:\\Users\\Niraj adh\\Downloads"};
    char openpath[200];
    printf("                 IMAGE FILTER        \n\n");
    printf("Images of DESKTOP   :\n");
    printf("\n");
    listf(deskpath);
    printf("\n");
    printf("Images of PICTURES  :\n");
    printf("\n");
    listf(picpath);
    printf("\n");
    printf("Images of Downloads :\n");
    printf("\n");
    listf(downpath);
    printf("\n");

    char image[100];

    printf("SEARCH IMAGE : ");
    fgets(image, sizeof(image), stdin);
    image[strcspn(image, "\n")] = '\0';

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
        }
        }
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
                printf("%s\n", dir->d_name);
            }
        }
        closedir(d);
        return;
    }
}



int searchimg(char *openpath){
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
    }
    // Close the file
    fclose(file);
    return 0;
}