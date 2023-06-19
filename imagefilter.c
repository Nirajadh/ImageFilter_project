#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <dirent.h>
#include <string.h>

char infile[30];

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
} BMPHeader; // yo structure chai bmp file ko headers ko structure ho
typedef struct
{
    uint8_t rgbtBlue;
    uint8_t rgbtGreen;
    uint8_t rgbtRed;
} pixel;          // yo chai pixel ho
#pragma pack(pop) // pop le chai default setting ma laijancha

//{FUNCTION Declaretion
void listf(char *path);
int searchimg(char *openpath);
int dirdis();
void grayscale(int height, int width, pixel image[height][width]);

//
int main()
{
    dirdis();
    FILE *inputf = fopen(infile, "rb");

    if (inputf == NULL)
    {
        fclose(inputf);
        printf("\nCould not open input img");
        return 0;
    }
    FILE *outf = fopen("out.bmp", "wb");
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

    // grayscale apply
    grayscale(height, width, image);

    // write data to output file
    for (int i = 0; i < height; i++)
    {
        fwrite(image[i], sizeof(pixel), width, outf);
        for (int j = 0; j < padding; j++)
        {
            fputc(0x00, outf);
        }
    }

    free(image);
    fclose(inputf);
    fclose(outf);
}
//

// functions

int dirdis()
{
    char *deskpath = {"C:\\Users\\Niraj adh\\desktop"};
    char *picpath = {"C:\\Users\\Niraj adh\\Pictures"};
    char *downpath = {"C:\\Users\\Niraj adh\\Downloads"};
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

                return 1;
            }
        }
    }
    strcpy(infile, openpath);
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
                printf("%s\n", dir->d_name);
            }
        }
        closedir(d);
        return;
    }
}

//filter functions
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
