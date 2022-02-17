#ifndef Q3_H
#define Q3_H

#include "image.h"
#define THRESHOLD_ZERO 0 

#define GET_GRAY_VALUE_OF_SEGMENT(i,N) ((i)*(255/((N)-1))) /*the formula how to calculate the color a segment*/


/*
creates image and according to the list of segments we get and the size
 we paint according to a formula every segment in his specific color
 */
grayImage* colorSegments(grayImage* img, imgPosCell** segments, Uint size);

/*
this function gets the first segment in the segment list and the color we should
print all the segment and paint all we need in the new image we created
 */
void paintSegment(imgPosCell* seg, grayImage* res, Uchar color);

#endif Q3_H