#ifndef Q6_H
#define Q6_H

#include "q5.h"

/*
get a name for a compressed pgm image in a binary file and an output pgm file
read the binary data, decompress and print it to the pgm file
*/
void convertCompressedImageToPGM(char* compressed_file_name, char* pgm_file_name);

/*
main deCompression function
responsible for handling all indexes and amounts, allocations
and calls to relevant components of the decompression algorithm
*/
void deCompressAndPrintToPGM(FILE* fp, Ushort rows, Ushort cols, Ushort  bits, Uchar* stack, Ushort size, Ushort* row, Ushort* col);

/*
get a compressed pixel and the multiplication value and return the decompressed value
value will be the max of a possible range.
for example: if old value is: 248-255 ==> then new value is: 31, so 31 ==> 255
*/
Uchar oldPixelValue(Uchar pixel, Ushort multiplication);

/*
read relevant data for PGM image from the binary file
*/
void getBinaryPGMdata(FILE* bin_fp, Ushort* rows, Ushort* cols, Uchar* max);

/*
print PGM header information to image before pixels
*/
void printPGMdata(FILE* fp, Ushort cols, Ushort rows, Uchar max);

/*
get a mask for decompression algorithm.
depending on requested index.
*/
BYTE getMask(Ushort index);

#endif Q6_H