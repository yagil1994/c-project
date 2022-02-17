#ifndef Q5_h
#define Q5_h


#include "image.h"

#define BASE 2

/*
this function receives:
1. a file name
2. a grayImage structure (filled with concrete data),
3. reduced value key for the pixels
it compresses the pixels within the grayImage according to the value key
and prints them to a binary file name 'file_name.bin'
*/
void saveCompressed(char* file_name, grayImage* image, Uchar reduced_gray_levels);

/*
this function receives:
1. grayImage data structur
2. file name
3. reduced value key for the pixels
4. max amount of bits per pixel
it creates a binary file and compresses and prints the image (including all the relevant data) to it
closes the file when done
*/
void exportToBinary(grayImage* img, char* fname, Uchar reduced_gray_levels, Ushort bitsAmount);


/*
this function receives:
1. a binary file pointer
2. grayImage data structure
3. max amount of bits per pixel
compresses the pixels matrix and prints it out to the binary file
*/
void compressPixelsAndPrintToBinary(FILE* fp, grayImage* img, Ushort bitsAmount);

/*
the main compression function. handles all the allocation and indexes
calls the componenets of the compression algorithm
*/
void compressImage(Uchar* res, Uint size, Ushort bits, grayImage* img, Ushort* row, Ushort* col);

/*
will determine how many stack of bytes are needed to completely
go through all pixels for compression/decompression
*/
Uint howManyIterations(Uint totalSize, Uint stackSize);

/*
how many bytes are required to fully hold a stack of pixels
*/
Uint howManyBytes(Ushort bits);

/*
print the information of a PGM picture compressed to a binary file
*/
void printImageInfoToBinFile(grayImage* img, FILE* fp, Uchar maxGray);

/*
a function to determine the max amount of bits required to hold a reduced size pixel
*/
Ushort bitsPerCompressedPixel(Uchar reduced_gray_levels);

/*
how many bytes are required to hold the image in compressed version
*/
Uint compressedPixelsAmount(Ushort bitsAmount, Ushort rows, Ushort cols);

/*
return the reduced value for the pixel in the compressed image format
*/
Uchar reducedPixelValue(Uchar pixel, Ushort division);

#endif Q5_h