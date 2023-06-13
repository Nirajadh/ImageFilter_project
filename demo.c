#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <dirent.h>
#include <string.h>
#pragma pack(push, 1) // pragma le chai structure ko members lai tightly pack garcha.padding haru huna dinna so file read and write garna sajilo huncha ra file ko size ni ghatcha.{ #pragma le chai compiler lai instruction dini kam garcha ,pack le chai element of structure kasari store huncha vanni ho ,yo use garera emements bich padding haru milauna milcha , push use garera chai hamiley temporiraly pack setting change garna milcha,1 chai 1byte boundry ho - row ko elements lai 1 ko multiple ho ki  nai check garcha ani ho vane padding add gardaina. 1 vako huna le padding add hunna  }overall purpose nai padding bina banauna ho.
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

void grayscale(int height, int width, pixel image[height][width]);

int main()
{
    printf("                         IMAGE FILTER                  ");
    DIR *d;
    struct dirent *dir;
    d = opendir("C:\\Users\\Niraj adh\\Downloads\\demo\\images");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    char n[100] = {"C:\\Users\\Niraj adh\\Downloads\\demo\\images\\"};
    char m[50] = {""};
    printf("enter name of the image : ");
    gets(m);
    strcat(n, m);
    puts(n);
    FILE *inputf = fopen(n, "rb");
    if (inputf == NULL)
    {
        fclose(inputf);
        printf("Could not open img");
        return 0;
    }
    FILE *outf = fopen("C:\\Users\\Niraj adh\\Pictures\\image filter\\out.bmp", "wb");
    if (outf == NULL)
    {
        fclose(inputf);
        printf("Could not create img");
        return 0;
    }
    BMPHeader header;

    fread(&header, sizeof(BMPHeader), 1, inputf);
    int height = abs(header.height_px); // abs vaneko absolute value ko lagi ho (- ma vaye positive value aaucha)kunai format ma image upside doen store huna sakcha tesailey height negayivr huna sakcha
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
    return 0;
}
// grayscale filter apply garni function
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
