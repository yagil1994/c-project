#ifndef Q4_H
#define Q4_H

#include "image.h"

/*
get file name for a PGM formatted image
read it and creat a grayImage struct from it's data
*/
grayImage* readPGM(char* fname);

/*
get a grayImage data type that already has rows and cols
get a PGM file pointed in the first actual pixel data location
assign all pixel data to the grayImage pixels
*/
void assignDataToGrayImage(grayImage* img, FILE* fp);

/*
check if the PGM file version is compatible with this program
otherwise - exit
*/
void PGMversionCheck(char* version);

#endif Q4_H


