#include "q4.h"


/*****************static functions declarations*****************/
/*
get a PGM file pointer (to the beggining of the file)
get pointers for version, rows, cols, max value
scan the appropriate data from the PGM file to the relevant variables.
*/
static void getImgData(FILE* fp, Ushort* rows, Ushort* cols);

/*
these function handle the header of a PGM image file.
gets the version (and verify compatibility)
skip comments (comments are expected only between version line and cols&rows line)
get the cols and rows and max gray value. (max gray value is dumped)
*/
static void getVersion(FILE* fp);
static void skipComments(FILE* fp);
static void getRowsCols(FILE* fp, Ushort* rows, Ushort* cols);
/*****************static functions declarations*****************/


grayImage* readPGM(char* fname)
{
    FILE* fp = fileOpenProcedure(fname, "r");
    Ushort rows = 0, cols = 0;
    getImgData(fp, &rows, &cols);
    grayImage* img = allocateGrayImage(rows, cols);
    assignDataToGrayImage(img, fp);
    fclose(fp);
    return img;
}

void assignDataToGrayImage(grayImage* img, FILE* fp) {
    Ushort i = 0, j=0, size = (img->rows) * (img->cols);
    int pixData;
    for (i = 0; i < img->rows; i++)
    {
        for ( j = 0; j < img->cols; j++)
        {
            fscanf(fp, "%d", &pixData);
            img->pixels[i][j] = (Uchar)pixData;
        }
    }
}


void PGMversionCheck(char* version) {
    if (strcmp(version, COMPATIBLE_VERSION))
    {
        printf("incompatible PGM version\n");
        exit(COMPATIBILITY_ERROR);
    }
}

/*****************static functions implementations*****************/

static void getImgData(FILE* fp, Ushort* rows, Ushort* cols)
{
    getVersion(fp);
    skipComments(fp);
    getRowsCols(fp, rows, cols);
}

static void getVersion(FILE* fp) {
    char* version = (char*)malloc(MAX_VERSION_LENGTH * sizeof(char)); /*version of a PGM file is: "Px", while x represents a number*/
    checkAlloc(version);
    char c = fgetc(fp);
    if (c == 'P') 
    {
        version[0] = c;
        fscanf(fp, "%s", (version + 1));
    }
    else
    {
        printf("PGM file data is invalid. exiting\n");
        exit(INVALID_DATA_IN_FILE);
    }
    PGMversionCheck(version);
    free(version);
}

static void skipComments(FILE* fp) {
    char* comment = (char*)malloc(COMMENTSIZE * sizeof(char));
    checkAlloc(comment);
    Ushort counter = 1;
    char c = fgetc(fp);
    while (c == NEWLINE)
    {
        c = fgetc(fp);
        counter++;
        if (c == HASH)
        {
            fgets(comment, COMMENTSIZE, fp);
        }
        else
        {
            fseek(fp, -(counter + 1), SEEK_CUR);
        }
    }
    free(comment);
}


static void getRowsCols(FILE* fp, Ushort* rows, Ushort* cols)
{
    int max;
    fscanf(fp, "%hu %hu %d", cols, rows, &max);
    if ((*rows) == 0 || (*cols) == 0)
    {
        printf("PGM file data is probably empty. exiting\n");
        exit(EMPTY_PGM_FILE);
    }
}
/*****************static functions implementations*****************/
