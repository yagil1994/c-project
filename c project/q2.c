#include "q2.h"

/*****************static functions declarations*****************/

/*
compares two imgPosCells according to their cols location,
and row in case they are in the same row,returns true if a should be before b else return false
*/
static BOOL compareCellsForSort(imgPosCell* a, imgPosCell* b);

/*converts a treeNode to a list of locations*/
static imgPosCell* convertTreeNodeToList(treeNode* root, BOOL** visitingarray);

/*this function adds an imgPosCell in a sorted way to a location lists
according to the position of the imgPosCell we want to add-increasing sort*/
static void AuxConvertTnodeToImgPosCell(treeNode* root, imgPosCell** first, BOOL** visitingarray);

static void SortedAddTolocationsList(imgPosCell** first, imgPosCell* add);

/*
merging-we use it with merge sort to merge two "parts" to one
*/
static void merge(PosList* dest, PosList* arr1, int size1, PosList* arr2, int size2);

/*
adds a location cell to the location list
*/
static void addToPosList(PosList** Poslst, imgPosCell* add, int sizeOfAddList, int* PosListLogS, int* PosListphyS);

/*****************static functions declarations*****************/


Uint findAllSegments(grayImage* img, Uchar threshold, imgPosCell*** segments)
{
	if (isEmptyImg(img->rows, img->cols))
		return 0;
	int PosListphyS = 2, PosListLogS = 0, i;
	Segment* currSeg;
	PosList* tmpPosList = (PosList*)malloc(sizeof(PosList) * (PosListphyS));
	checkAlloc(tmpPosList);
	imgPosCell* tmp;
	imgPos kernel;
	BOOL** visitingArray = makeVisitingArray(img);
	BOOL flag = FALSE;
	/*finds the first available minimum gray cell and returns by reference to flag if there is, if not we dont enter the loop*/
	findMinGrayCell(img, visitingArray, &flag, kernel);
	while (flag)/*run this loop as long as we have "available" segments to work with -according to flag*/
	{
		currSeg = findSingleSegment(img, kernel, threshold);
		tmp = convertTreeNodeToList(currSeg->root, visitingArray);
		addToPosList(&tmpPosList, tmp, currSeg->size, &PosListLogS, &PosListphyS);
		FreeSegment(currSeg);
		flag = FALSE;
		findMinGrayCell(img, visitingArray, &flag, kernel);/*find the next minimum gray cell, if there is not quit the loop*/
	}
	tmpPosList = (PosList*)realloc(tmpPosList, sizeof(PosList) * PosListLogS);
	checkAlloc(tmpPosList);
	mergeSort(tmpPosList, PosListLogS);
	*segments = (imgPosCell**)malloc(sizeof(imgPosCell*) * PosListLogS);
	checkAlloc(*segments);
	for (i = 0; i < PosListLogS; i++)
	{
		(*segments)[i] = tmpPosList[i].first;
	}
	free(tmpPosList);
	freeVisitingArr(visitingArray, img->rows);
	return PosListLogS;/*returning the final size of the array*/
}
imgPosCell* createNewimgPosCell(imgPos pos, imgPosCell* next, imgPosCell* prev)
{
	imgPosCell* res = (imgPosCell*)malloc(sizeof(imgPosCell));
	checkAlloc(res);
	res->position[0] = pos[0];
	res->position[1] = pos[1];
	res->next = next;
	res->prev = prev;
	return res;
}
void findMinGrayCell(grayImage* img, BOOL** visitingArray, BOOL* flag, imgPos min)
{
	int i, j;
	Uchar MinGrayValue, TmpGrayValue;
	imgPos loc;
	for (i = 0; i < img->rows; i++)
	{
		loc[0] = i;
		for (j = 0; j < img->cols; j++)
		{
			loc[1] = j;
			if (visitingArray[loc[0]][loc[1]] == FALSE)/*visiting array == FALSE --> location is available --> check it*/
			{
				if (*flag == FALSE)
				{
					MinGrayValue = img->pixels[loc[0]][loc[1]];
					min[0] = loc[0];
					min[1] = loc[1];
					*flag = TRUE;/*updating we have the first already*/
				}
				else
				{
					TmpGrayValue = img->pixels[loc[0]][loc[1]];
					if (TmpGrayValue < MinGrayValue)
					{
						MinGrayValue = TmpGrayValue;
						min[0] = loc[0];
						min[1] = loc[1];
					}
				}
			}

		}
	}
}

static imgPosCell* convertTreeNodeToList(treeNode* root, BOOL** visitingArray)
{
	imgPosCell* first = NULL;
	AuxConvertTnodeToImgPosCell(root, &first, visitingArray);
	return first;
}

static void AuxConvertTnodeToImgPosCell(treeNode* root, imgPosCell** first, BOOL** visitingArray)
{
	imgPos loc;
	imgPosCell* curr;
	int i = 0;
	loc[0] = root->position[0];
	loc[1] = root->position[1];
	if (visitingArray[loc[0]][loc[1]] == FALSE)
	{
		curr = createNewimgPosCell(loc, NULL, NULL);
		SortedAddTolocationsList(first, curr);/*add the root before his children*/
		visitingArray[loc[0]][loc[1]] = TRUE;
	}
	while (root->similar_neighbors[i])/*as long as we have neighbors we need to get their "valid" neighbors*/
	{
		loc[0] = root->similar_neighbors[i]->position[0];
		loc[1] = root->similar_neighbors[i]->position[1];
		AuxConvertTnodeToImgPosCell(root->similar_neighbors[i], first, visitingArray);
		i++;
	}
}

void SortedAddTolocationsList(imgPosCell** first, imgPosCell* add)
{
	imgPosCell* curr;
	if (*first == NULL)
	{
		*first = add;
		return;
	}
	if (compareCellsForSort(*first, add) == FALSE)/*it means "add" should be before the first*/
	{
		add->next = *(first);
		(*first)->prev = add;
		(*first) = add;
		return;
	}
	else
	{
		curr = *first;
		while (curr->next) /*if we need to add in the middle*/
		{
			if (compareCellsForSort(curr, add) == FALSE)
			{
				add->next = curr;
				add->prev = curr->prev->next;
				curr->prev->next = add;
				curr->prev = add;
				return;
			}
			curr = curr->next;
		}
		/*if we need to add in the end*/
		if (compareCellsForSort(curr, add) == FALSE)/*it means "add" should be before the last one*/
		{
			add->next = curr;
			add->prev = curr->prev->next;
			curr->prev->next = add;
			curr->prev = add;
		}
		else
		{/*it means "add" should be the last one*/

			curr->next = add;
			add->prev = curr;
		}
	}
}

static BOOL compareCellsForSort(imgPosCell* a, imgPosCell* b)
{
	if (a->position[1] < b->position[1])/*if the col of a is before b we need to put a before b*/
		return TRUE;
	else if ((a->position[1] == b->position[1]))/*if a and b have are in the same col we need to put the one that located in a lower row */
	{
		if ((a->position[0] < b->position[0]))
			return TRUE;
		else
			return FALSE;
	}
	else
		return FALSE;/*if a should be before 'b' return true else return false*/
}

static void addToPosList(PosList** Poslst, imgPosCell* add, int sizeOfAddList, int* PosListLogS, int* PosListphyS)
{
	PosList* tmp = *Poslst;
	int PosListphyS_Tmp = *PosListphyS;
	int PosListLogS_Tmp = *PosListLogS;
	if (PosListLogS_Tmp == 0)/*if the Pos list is empty we need to insert in in the beggining according to the array size*/
	{
		tmp[PosListLogS_Tmp].first = add;
		tmp[PosListLogS_Tmp].size = sizeOfAddList;
		PosListLogS_Tmp++;
	}
	else
	{/*we add the location cell to the end of the array*/
		if (PosListLogS_Tmp >= PosListphyS_Tmp)/*in case we need to increase the physical size of the array*/
		{
			PosListphyS_Tmp *= 2;
			tmp = (PosList*)realloc(tmp, PosListphyS_Tmp * sizeof(PosList));
			checkAlloc(tmp);
		}
		tmp[PosListLogS_Tmp].first = add;
		tmp[PosListLogS_Tmp].size = sizeOfAddList;
		PosListLogS_Tmp++;
	}
	*PosListphyS = PosListphyS_Tmp;
	*PosListLogS = PosListLogS_Tmp;
	*Poslst = tmp;
}

void mergeSort(PosList* Poslst, int size)
{
	int i;
	PosList* merged;
	if (size == 1)
	{
		return;
	}
	else
	{
		mergeSort(Poslst, size / 2);
		mergeSort(Poslst + (size / 2), size - (size / 2));
		merged = (PosList*)malloc(sizeof(PosList) * size);
		checkAlloc(merged);
		merge(merged, Poslst, size / 2, Poslst + (size / 2), size - (size / 2));
		for (i = 0; i < size; i++)
		{
			Poslst[i] = merged[i];
		}
		free(merged);
	}
}

static void merge(PosList* dest, PosList* arr1, int size1, PosList* arr2, int size2)
{
	int i = 0, j = 0, writing_ind = 0;
	while (i < size1 && j < size2)
	{
		if (arr1[i].size > arr2[j].size)
		{
			dest[writing_ind] = arr1[i];/*keep updating the destination array*/
			i++;
		}
		else
		{
			dest[writing_ind] = arr2[j];/*keep updating the destination array*/
			j++;
		}
		writing_ind++;
	}
	while (i < size1)
	{
		dest[writing_ind] = arr1[i];/*keep updating the destination array*/
		i++;
		writing_ind++;
	}
	while (j < size2)
	{
		dest[writing_ind] = arr2[j];/*keep updating the destination array*/
		j++;
		writing_ind++;
	}
}