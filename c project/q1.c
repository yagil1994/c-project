#include "q1.h"

/*****************static functions declarations*****************/

static void findSingleSegmentAux(grayImage* img, treeNode* root, Uchar kernelGrayValue, Uchar threshold, Uint* MainSize, BOOL** visitingArray);
/*****************static functions declarations*****************/

Segment* findSingleSegment(grayImage* img, imgPos kernel, Uchar threshold)
{
	if (isEmptyImg(img->rows, img->cols))
	{
		return NULL;
	}
	Segment* seg;
	Uchar kernelGrayValue = img->pixels[kernel[0]][kernel[1]];
	BOOL** visitingArray = makeVisitingArray(img);/*making an array of arrays that will let us know previous "visiting"*/
	seg = (Segment*)malloc(sizeof(Segment));
	checkAlloc(seg);
	seg->root = createTreeNode(kernel, NULL);
	seg->size = 1;/*counting one for the root itself*/
	findSingleSegmentAux(img, seg->root, kernelGrayValue, threshold, &(seg->size), visitingArray);
	freeVisitingArr(visitingArray, img->rows);
	return seg;
}

static void findSingleSegmentAux(grayImage* img, treeNode* root, Uchar kernelGrayValue, Uchar threshold, Uint* MainSize, BOOL** visitingArray)
{
	visitingArray[root->position[0]][root->position[1]] = TRUE;/*updating that the current root in the visiting array*/
	treeNode** RealNeighbors;
	int i = 0;
	GetNeighborsInRange(img, root, &RealNeighbors, visitingArray, kernelGrayValue, threshold);
	root->similar_neighbors = RealNeighbors;/*updating the root similar similar_neighbors*/
	(*MainSize)++;
	while (RealNeighbors[i])/*as long as we have neighbors we need to get their "valid" neighbors*/
	{
		findSingleSegmentAux(img, root->similar_neighbors[i], kernelGrayValue, threshold, MainSize, visitingArray);
		i++;
	}
}

void GetNeighborsInRange(grayImage* img, treeNode* root, treeNode*** PRealNeighbors, BOOL** visitingArray, Uchar kernelGrayValue, Uchar threshold)
{
	short writing_ind = 0, rows, cols;
	imgPos location;
	BOOL flag;
	treeNode** tmp = (treeNode**)malloc(sizeof(treeNode*) * (MAX_NEIGHBORS + 1));/*+1 for the NULL at the end of the array*/
	checkAlloc(tmp);
	for (rows = root->position[0] - 1; rows < root->position[0] + 2; rows++)
	{
		location[0] = rows;
		for (cols = root->position[1] - 1; cols < root->position[1] + 2; cols++)
		{
			if (rows == root->position[0] && cols == root->position[1])/*skipping the root itself*/
				cols++;
			location[1] = cols;
			flag = isValidNeighbor(img, location, visitingArray, kernelGrayValue, threshold);
			if (flag)/*if the neighbor is valid -> add him to the array & update the visiting array*/
			{
				tmp[writing_ind] = createTreeNode(location, NULL);
				visitingArray[location[0]][location[1]] = TRUE;
				writing_ind++;
			}
		}
	}
	if (writing_ind != MAX_NEIGHBORS)
	{
		tmp = (treeNode**)realloc(tmp, sizeof(treeNode*) * (writing_ind + 1));/*+1 for NULL*/
		checkAlloc(tmp);
	}
	tmp[writing_ind] = NULL;
	*PRealNeighbors = tmp;
}

BOOL isValidNeighbor(grayImage* img, imgPos location, BOOL** visitingArray, Uchar kernelGrayValue, Uchar threshold)
{
	Uchar neighborGrayValue;
	if (((location[0] >= 0) && (location[0] < img->rows)) && ((location[1] >= 0) && (location[1] < img->cols)))
	{
		if (visitingArray[location[0]][location[1]] == FALSE)/*if the neighbor is not occupied we can "use him" */
		{
			neighborGrayValue = img->pixels[location[0]][location[1]];
			if (isMatchingNeighbor(kernelGrayValue, neighborGrayValue, threshold))/*if the neighbor is in the range of the threshold of the kernel*/
				return TRUE;
		}
	}
	return FALSE;
}

BOOL isMatchingNeighbor(Uchar kernelGrayValue, Uchar GrayValueNeighbor, Uchar threshold)
{
	return (abs(kernelGrayValue - GrayValueNeighbor) <= threshold);
}

BOOL isEmptyImg(short rows, short cols)
{
	return (rows == 0) || (cols == 0);
}
