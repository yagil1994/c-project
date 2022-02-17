#ifndef Q1_H
#define Q1_H
#include "trees.h"
#define MAX_NEIGHBORS 8


/*the function finds a segment according to the kernel it gets and to the threshold,
it creates it and returns in the end
if the image is empty returns NULL*/
Segment* findSingleSegment(grayImage* img, imgPos kernel, Uchar threshold);

/*
returns true if the neighbor is in a
valid range from the kernel,returns false if not
*/
BOOL isMatchingNeighbor(Uchar kernelGrayValue, Uchar GrayValueNeighbor, Uchar threshold);

/*
returns true is the neighbor is valid-if no one
"used" him as a neighbor before and
he is in a valid location in the image and
as well if he stands with the requiement of the threshold of the kernel
*/
BOOL isValidNeighbor(grayImage* img, imgPos location, BOOL** visitingArray, Uchar kernelGrayValue, Uchar threshold);

/*
gets all the 'valid" neighbors in the range according
to the kernel,it updates 'RealNeighbors' by reference
*/
void GetNeighborsInRange(grayImage* img, treeNode* root, treeNode*** PRealNeighbors, BOOL** visitingArray, Uchar kernelGrayValue, Uchar threshold);

/*if the rows are 0 and the cols are 0 so the img is empty*/
/*returns TRUE if the image is empty, else return FALSE*/
BOOL isEmptyImg(short rows, short cols);

#endif Q1_H