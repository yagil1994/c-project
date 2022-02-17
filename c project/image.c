#include "image.h"

BOOL** makeVisitingArray(grayImage* img)
{
	/*
	creates a boolean board that after the creation all of his "cells" are initialized to false
	which means-unmaked- no neighbor was there
	*/
	int i;
	BOOL** visitingArray = (BOOL**)malloc(sizeof(BOOL*) * (img->rows));/*making an array of arrays that will let us know previous "visiting"*/
	checkAlloc(visitingArray);

	/*
	initializing the array to false-false means none visits and true means the opposite
	*/
	for (i = 0; i < img->rows; i++)
	{
		visitingArray[i] = (BOOL*)calloc(img->cols, sizeof(BOOL));
		checkAlloc(visitingArray[i]);
	}
	return  visitingArray;
}

void freeVisitingArr(BOOL** visitingArr, unsigned short rows)
{
	/*free visting array board */
	Ushort i;
	for (i = 0; i < rows; i++)
	{
		free(visitingArr[i]);
	}
	free(visitingArr);
}
void freeImgPosCell(imgPosCell* locationCell, unsigned int freeSize)
{
	/*free imgPosCell */
	imgPosCell* save, * curr = locationCell;
	Uint i = 0;
	while (i < freeSize - 1)
	{
		save = curr->next;
		free(curr);
		curr = save;
		i++;
	}
	free(curr);/*free manually the last one for preventing from exceeding the array*/
}

grayImage* allocateGrayImage(unsigned short rows, unsigned short cols) {
	grayImage* img = (grayImage*)malloc(sizeof(grayImage));
	checkAlloc(img);
	img->rows = rows;
	img->cols = cols;
	img->pixels = allocatePixels(rows, cols);
	return img;
}

unsigned char** allocatePixels(unsigned short rows, unsigned short cols) {
	Uchar** pixels = (Uchar**)malloc((sizeof(Uchar*)) * rows);
	checkAlloc(pixels);
	Ushort i;
	for (i = 0; i < rows; i++)
	{
		pixels[i] = (Uchar*)malloc((sizeof(Uchar)) * cols);
		checkAlloc(pixels[i]);
	}
	return pixels;
}

void freeGrayImage(grayImage* img) {
	Ushort i = 0;
	for (i = 0; i < img->rows; i++)
	{
		free(img->pixels[i]);
	}
	free(img->pixels);
	free(img);
}


/*
this function is for testing purposes
*/
void printGrayImageToStream(grayImage* img, FILE* stream, Uchar max) {
	Ushort i = 0, j = 0;
	fprintf(stream,"P2\n%d %d\n%d\n", img->cols, img->rows, max);
	for (i = 0; i < img->rows; i++)
	{
		for (j = 0; j < img->cols; j++)
		{
			fprintf(stream,"%d\t", img->pixels[i][j]);
		}
		fseek(stream, -1, SEEK_CUR);
		fputc(NEWLINE, stream);
	}
}
