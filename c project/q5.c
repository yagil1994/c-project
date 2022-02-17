#include "q5.h"


/*****************static functions declarations*****************/
/*these function are parts of the compression algorithm*/
static void insertPixelInWhole(Uchar pix, Uchar* res, Ushort c, Ushort bits, Ushort* space, Ushort* r);
static void insertRemainingPixel(Uchar pix, Uchar* res, Ushort c, Ushort bits, Ushort* space, Ushort* r);
static void insertPartialPixel(Uchar pix, Uchar* res, Ushort c, Ushort bits, Ushort* space, Ushort* r);

/*****************static functions declarations*****************/

void saveCompressed(char* file_name, grayImage* image, Uchar reduced_gray_levels)
{
    Ushort bitsAmount = bitsPerCompressedPixel(reduced_gray_levels);
    char* newFname = replaceFileFormat(file_name, "pgm", "bin");
    exportToBinary(image, newFname, reduced_gray_levels, bitsAmount);
    free(newFname);
}

void exportToBinary(grayImage* img, char* fname, Uchar reduced_gray_levels, Ushort bitsAmount)
{
    FILE* fp = fileOpenProcedure(fname, "wb");
    printImageInfoToBinFile(img, fp, reduced_gray_levels - 1);
    compressPixelsAndPrintToBinary(fp, img, bitsAmount);
    fclose(fp);
}

void printImageInfoToBinFile(grayImage* img, FILE* fp, Uchar maxGray)
{
    fwrite(&img->rows, sizeof(Ushort), 1, fp);
    fwrite(&img->cols, sizeof(Ushort), 1, fp);
    fwrite(&maxGray, sizeof(Uchar), 1, fp);
}

void compressPixelsAndPrintToBinary(FILE* fp, grayImage* img, Ushort bitsAmount)
{
    Uint comp_size = compressedPixelsAmount(bitsAmount, img->rows, img->cols);
    Uint bytesPerStack = howManyBytes(bitsAmount), iterations;
    Uchar* stack; 
    Ushort row = 0, col = 0, i;
    iterations = howManyIterations(comp_size, bytesPerStack);
    for (i = 0; i < iterations; i++)
    {
        stack = (Uchar*)calloc(bytesPerStack, sizeof(Uchar));
        checkAlloc(stack);
        compressImage(stack, bytesPerStack, bitsAmount, img, &row, &col);
        fwrite(stack, sizeof(Uchar), bytesPerStack, fp);
        free(stack);
    }
}

void compressImage(Uchar* res, Uint size, Ushort bits, grayImage* img, Ushort* row, Ushort* col)
{
    Ushort div = (power(BASE, BITS_IN_BYTE - bits)), c = 0; /*c: stack index*/
    Ushort space = BITS_IN_BYTE, r = bits; 
    /*space: space in target byte. r: remainder of unhandeled bits in pixel*/
    Uchar pix;
    while ((*row) < img->rows)
    {
        if ((*col) >= img->cols)
        {
            (*col) = 0;
        }
        while ((*col) < img->cols)
        {
            if (c == size)
            {
                return;
            }
            pix = reducedPixelValue(img->pixels[(*row)][(*col)], div);
            r = bits;
            while (r > 0) /*inner loop to compress a pixel*/
            {
                if (space >= r)
                {
                    if (r == bits)
                    {
                        insertPixelInWhole(pix, res, c, bits, &space, &r);
                    }
                    else
                    {
                        insertRemainingPixel(pix, res, c, bits, &space, &r);
                    }
                }
                else
                {
                    insertPartialPixel(pix, res, c, bits, &space, &r);
                }

                if (space == 0)
                {
                    c++;
                    space = BITS_IN_BYTE;
                }
            }
            (*col)++;
        }
        (*row)++;
    }
}

Uint howManyIterations(Uint totalSize, Uint stackSize)
{
    if (totalSize % stackSize == 0)
    {
        return totalSize / stackSize;
    }
    else
    {
        return (totalSize / stackSize) + 1;
    }
}

Uint howManyBytes(Ushort bits)
{
    Uint counter = 1, totalBits = BITS_IN_BYTE;
    while ((totalBits % bits) != 0)
    {
        counter++;
        totalBits += BITS_IN_BYTE;
    }
    return counter;
}


Ushort bitsPerCompressedPixel(Uchar reduced_gray_levels)
{
    int counter = 0;
    if (reduced_gray_levels == 0)
    {
        printf("invalid 'reduced_gray_levels', exiting...\n");
        exit(COMPATIBILITY_ERROR);
    }
    while (reduced_gray_levels / BASE) {
        counter++;
        reduced_gray_levels /= BASE;
    }
    return counter;
}

Uint compressedPixelsAmount(Ushort bitsAmount, Ushort rows, Ushort cols)
{
    Uint total = (bitsAmount * rows * cols);
    if (total % BITS_IN_BYTE == 0)
    {
        return total / BITS_IN_BYTE;
    }
    else
    {
        return (total / BITS_IN_BYTE) + 1;
    }
}

Uchar reducedPixelValue(Uchar pixel, Ushort division) {
    if (pixel == 0)
    {
        return 0;
    }
    else if (pixel / division == 0)
    {
        return 1;
    }
    else
    {
        return (pixel) / (division);
    }
}



/*****************static functions implementations*****************/

static void insertPixelInWhole(Uchar pix, Uchar* res, Ushort c, Ushort bits, Ushort* space, Ushort* r)
{
    (*space) -= (*r);
    res[c] |= (pix << (*space));
    (*r) = 0;
}

static void insertRemainingPixel(Uchar pix, Uchar* res, Ushort c, Ushort bits, Ushort* space, Ushort* r)
{
    (*space) -= (*r);
    res[c] |= (pix << (*space));
    (*r) = 0;
}

static void insertPartialPixel(Uchar pix, Uchar* res, Ushort c, Ushort bits, Ushort* space, Ushort* r)
{
    (*r) -= (*space);
    res[c] |= (pix >> (*r));
    (*space) = 0;
}


