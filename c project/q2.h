#ifndef Q2_H
#define Q2_H

#include "q1.h"

/*
this function finds all the segments in the img and returns them by reference with segments
every imgPosCell in the array points on the first location on a certain segment,
the function will return in the end the size of the array
*/
Uint findAllSegments(grayImage* img, Uchar threshold, imgPosCell*** segments);

void findMinGrayCell(grayImage* img, BOOL** visitingArray, BOOL* flag, imgPos min);

/*a recursive function that gets a an array of potisions lists and sorted them in a decreasing sort-from the big to the small*/
void mergeSort(PosList* Poslst, int size);

/*creating a newPosCell*/
imgPosCell* createNewimgPosCell(imgPos pos, imgPosCell* next, imgPosCell* prev);

#endif Q2_H