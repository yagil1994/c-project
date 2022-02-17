#ifndef IMAGE_H
#define IMAGE_H
#include "service_funcs.h"

#define HASH '#'
#define COMMENTSIZE 100 
#define MAX_VERSION_LENGTH 3
#define COMPATIBLE_VERSION "P2"

/*****typedefs*****/

/*location in the image imgPos[0]=row, imgPos[1]=col*/
typedef unsigned short imgPos[2];

/*gray image struct*/
typedef struct _grayImage
{
	unsigned short rows, cols;
	unsigned char** pixels;
}grayImage;

/*
struct of that has a position of pixel in a list and pointer to the next
pixel in the list and for the prevoius one (NULL there is not one before or after)
*/
typedef struct _imgPosCell
{
	imgPos position;
	struct _imgPosCell* next, * prev;
}imgPosCell;

/*
struct that has a pointer to a location list and the size of the list
*/
typedef struct _PosList
{
	imgPosCell* first;
	unsigned short size;
} PosList;


/******declarations******/

/*
get rows and cols
allocate space for a grayImage data type.
including it's internal pixel array.
*/
grayImage* allocateGrayImage(unsigned short rows, unsigned short cols);
unsigned char** allocatePixels(unsigned short rows, unsigned short cols);
/*
free a grayImage data type
will free all pixels one-by-one
*/
void freeGrayImage(grayImage* img);

/*
a general function to print a grayImage
send stream = stdout to print to terminal
otherwise send a file pointer
*/
void printGrayImageToStream(grayImage* img, FILE* stream, Uchar max);

/*
making an array of arrays that will let us know
previous "visiting"-any location that it is true symbolys the location is occupied, false means free
*/
BOOL** makeVisitingArray(grayImage* img);

/*
free the visitingArray
*/
void freeVisitingArr(BOOL** visitingArr, unsigned short rows);

/*
free imgposCell
*/
void freeImgPosCell(imgPosCell* locationCell, unsigned int freeSize);

#endif IMAGE_H