#include "q3.h"

grayImage* colorSegments(grayImage* img, imgPosCell** segments, Uint size)
{
	Ushort i;
	Uchar color;
	grayImage* res;
	res = allocateGrayImage(img->rows, img->cols);
	if (size == 1)
	{
		paintSegment(*segments, res, THRESHOLD_ZERO);
	}
	else
	{
		for (i = 0; i < size; i++)
		{
			color = GET_GRAY_VALUE_OF_SEGMENT(i, size);
			paintSegment(segments[i], res, color);
		}
	}
	return res;
}
void paintSegment(imgPosCell* seg, grayImage* res, Uchar color)
{
	while (seg)
	{
		res->pixels[seg->position[0]][seg->position[1]] = color;
		seg = seg->next;
	}
}
