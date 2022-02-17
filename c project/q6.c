#include "q6.h"

/*****************static functions declarations*****************/
/*these function are parts of the decompression algorithm*/
static Uchar deCompressPixelInWhole(Uchar source, Ushort* space, Ushort* r, Ushort bits, Uchar pix);
static Uchar deCompressRemainigPixel(Uchar source, Ushort* space, Ushort* r, Ushort bits, Uchar pix);
static Uchar deCompressPartialPixel(Uchar source, Ushort* space, Ushort* r, Ushort bits, Uchar pix);


/*****************static functions declarations*****************/


void convertCompressedImageToPGM(char* compressed_file_name, char* pgm_file_name) {
    FILE* bin = fileOpenProcedure(compressed_file_name, "rb");
    FILE* pgm = fileOpenProcedure(pgm_file_name, "w");
    Ushort rows, cols, row=0, col = 0;
    Uchar max, *stack;
    getBinaryPGMdata(bin, &rows, &cols, &max);
    Ushort bits = bitsPerCompressedPixel(max + 1);
    Uint comp_size = compressedPixelsAmount(bits, rows, cols);
    Ushort bytesPerStack = howManyBytes(bits), multiplication = power(BASE, BITS_IN_BYTE - bits);
    Uint iterations = howManyIterations(comp_size, bytesPerStack), i;
    printPGMdata(pgm, cols, rows, oldPixelValue(max, multiplication));
    for (i = 0; i < iterations; i++)
    {
        stack = (Uchar*)calloc(bytesPerStack, sizeof(Uchar));
        checkAlloc(stack);
        fread(stack, sizeof(Uchar), bytesPerStack, bin);
        deCompressAndPrintToPGM(pgm, rows, cols, bits, stack, bytesPerStack, &row, &col);
        free(stack);
    }
    fclose(bin);
    fclose(pgm);
}

void getBinaryPGMdata(FILE* bin_fp, Ushort* rows, Ushort* cols, Uchar* max)
{
    fread(rows, sizeof(Ushort), 1, bin_fp);
    fread(cols, sizeof(Ushort), 1, bin_fp);
    fread(max, sizeof(Uchar), 1, bin_fp);
}


void printPGMdata(FILE* fp, Ushort cols, Ushort rows, Uchar max)
{
    fprintf(fp, "P2\n%d %d\n%d\n", cols, rows, max);
}

void deCompressAndPrintToPGM(FILE* fp, Ushort rows, Ushort cols,Ushort  bits,Uchar* stack, Ushort size, Ushort* row, Ushort* col)
{
    Ushort multiplication = power(BASE, BITS_IN_BYTE - bits);
    Ushort space, r = BITS_IN_BYTE, c = 0;
    /*space: space left in pixel. r: remaining bits not handled in byte. c: stack index*/
    Uchar pix;
    while ((*row) < rows)
    {
        if ((*col) >= cols)
        {
            (*col) = 0;
        }
        while ((*col) < cols)
        {
            pix = 0;
            space = bits;
            if (c == size) /*stack is full*/
            {
                return;
            }
            while (space > 0) /*inner loop to decompress every pixel*/
            {
                if (space <= r)
                {
                    if (space == bits)
                    {
                        pix = deCompressPixelInWhole(stack[c], &space, &r, bits, pix);
                    }
                    else
                    {
                        pix = deCompressRemainigPixel(stack[c], &space, &r, bits, pix);
                    }
                }
                else
                {
                    pix = deCompressPartialPixel(stack[c], &space, &r, bits, pix);
                }

                if (r == 0)
                {
                    c++;
                    r = BITS_IN_BYTE;
                }
            }
            fprintf(fp, "%d ", oldPixelValue(pix, multiplication));
            (*col)++;
        }
        fprintf(fp, "\n");
        (*row)++;
    }
}

BYTE getMask(Ushort index)
{
    BYTE masks[9] = { 0x00,0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF };
    return (masks[index]);
}

Uchar oldPixelValue(Uchar pixel, Ushort multiplication)
{
    if (pixel == 0)
    {
        return 0;
    }
    else if (pixel == 1)
    {
        return (pixel * multiplication);
    }
    else
    {
        return (pixel * multiplication) + (multiplication-1);
    }
}


/*****************static functions implementations*****************/

static Uchar deCompressPixelInWhole(Uchar source, Ushort* space, Ushort* r, Ushort bits, Uchar pix)
{
    Uchar mask;
    if ((*r) < BITS_IN_BYTE)
    {
        mask = getMask((*r));
        source &= mask;
    }
    (*r) -= (*space);
    mask = ~getMask((*r));
    mask &= source;
    pix |= (mask >> (*r));
    (*space) = 0;
    return pix;
}

static Uchar deCompressRemainigPixel(Uchar source, Ushort* space, Ushort* r, Ushort bits, Uchar pix)
{
    (*r) -= (*space);
    Uchar mask = ~getMask((*r));
    mask &= source;
    pix |= (mask >> (*r));
    (*space) = 0;
    return pix;
}

static Uchar deCompressPartialPixel(Uchar source, Ushort* space, Ushort* r, Ushort bits, Uchar pix)
{
    Uchar mask = getMask((*r));
    mask &= source;
    (*space) -= (*r);
    pix |= (mask << (*space));
    (*r) = 0;
    return pix;
}

