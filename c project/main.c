#include "q1.h"
#include "q2.h"
#include "q3.h"
#include "q4.h"
#include "q5.h"
#include "q6.h"
void q1Test();
void q2Test();
void q3Test();
void q456Tests();

void main()
{
	q1Test();
	q2Test();
	q3Test();
	q456Tests();
}

void q1Test()
{
	int i, j;
	unsigned char* board[] = { ",*$(","(])\0","dZnZ","c\\2*" };
	grayImage img;
	char c = '*';
	img.cols = img.rows = 4;
	img.pixels = board;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			char c = img.pixels[i][j];
			printf("%-4d", c);
		}
		printf("\n");
	}

	imgPos pos;
	pos[0] = 0;
	pos[1] = 3;
	Segment* res;
	res = findSingleSegment(&img, pos, 10);
	printTree(*res);
	FreeSegment(res);
}

void q2Test()
{
	Uint i, j;
	unsigned char* board[] = { ",*$(","(])\0","dZnZ","c\\2*" };
	grayImage img;
	char c = '*';
	img.cols = img.rows = 4;
	img.pixels = board;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			char c = img.pixels[i][j];
			printf("%-4d", c);
		}
		printf("\n");
	}

	imgPosCell** segments;
	imgPosCell* curr;
	imgPosCell* next;
	imgPosCell* head;
	unsigned int size = findAllSegments(&img, 10, &segments);
	for (i = 0; i < size; i++)
	{
		curr = segments[i];
		while (curr)
		{
			printf("(%d,%d)-> ", curr->position[0], curr->position[1]);
			curr = curr->next;
		}
		printf("\n");

	}
	if (segments)
	{
		for (i = 0; i < size; i++)
		{
			head = segments[i];
			while (head)
			{
				next = head->next;
				free(head);
				head = next;
			}
		}
		free(segments);
	}
}

void q3Test()
{
	int i, j;
	unsigned char* board[] = { ",*$(","(])\0","dZnZ","c\\2*" };
	grayImage img;
	char c = '*';
	img.cols = img.rows = 4;
	img.pixels = board;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
		  c = img.pixels[i][j];
			printf("%-4d", c);
		}
		printf("\n");
	}

	imgPosCell* arr[4];
	imgPos pos;
	imgPosCell* node[16];
	imgPosCell* next;
	imgPosCell* head;
	int writing = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			pos[0] = i;
			pos[1] = j;
			node[writing] = createNewimgPosCell(pos, NULL, NULL);
			writing++;
		}
	}
	node[0]->next = node[1];
	node[1]->next = node[5];
	node[5]->next = node[4];

	node[2]->next = node[6];

	node[3]->next = node[7];
	node[7]->next = node[11];
	node[11]->next = node[10];
	node[10]->next = node[9];
	node[9]->next = node[8];

	node[15]->next = node[14];
	node[14]->next = node[13];
	node[13]->next = node[12];
	arr[0] = node[0];
	arr[1] = node[2];
	arr[2] = node[3];
	arr[3] = node[15];
	grayImage* imgq3;
	imgq3 = colorSegments(&img, arr, 4);
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			unsigned char c = imgq3->pixels[i][j];
			printf("%-4d", c);
		}
		printf("\n");
	}
	freeGrayImage(imgq3);
	for (int i = 0; i < 4; i++)
	{
		 head = arr[i];
		while (head)
		{
			next = head->next;
			free(head);
			head = next;
		}
	}
}

void q456Tests()
{
	grayImage* img;
	img = readPGM("feep.ascii.enhanced.pgm");/*this tests q4*/
	saveCompressed("feep.ascii.enhanced.pgm", img, 32);/*this tests q5*/
	convertCompressedImageToPGM("feep.ascii.enhanced.bin", "feep.ascii.enhanced.new.pgm");/*this tests q6*/
	freeGrayImage(img);
}
