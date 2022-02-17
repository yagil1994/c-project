#include "service_funcs.h"

void checkAlloc(void* ptr) 
{
	if (!ptr)
	{
		printf("memory allocation error\n");
		exit(ALLOCATION_ERROR);
	}
}

void fileOpenCheck(FILE* fname) 
{
	if (!fname)
	{
		printf("file open failed\n");
		exit(FILE_OPEN_ERROR);
	}
}

void fileNameCheck(char* fname)
{
	if (!fname)
	{
		printf("file name invalid\n");
		exit(FILE_NAME_ERROR);
	}
}

int power(int base, int pow) {
	int i;
	int num = 1;
	for (i = 0; i < pow; i++)
	{
		num *= base;
	}
	return num;
}

char* replaceFileFormat(char* fname, char* currFormat, char* newFormat)
{
	Uint fnameS = strlen(fname), currFormatS = strlen(currFormat), newFormatS = strlen(newFormat), i, j;
	char* newFname = allocateString(fnameS - currFormatS + newFormatS + 1);
	for (i = 0; i < fnameS - currFormatS; i++)
	{
		newFname[i] = fname[i];
	}
	for (j = 0; j < newFormatS; j++)
	{
		newFname[i] = newFormat[j];
		i++;
	}
	newFname[i] = NULLCHAR;
	return newFname;
}

char* allocateString(int size)
{
	char* res = (char*)malloc(sizeof(char) * (size + 1));
	checkAlloc(res);
	return res;
}


FILE* fileOpenProcedure(char* name, char* mode) {
	fileNameCheck(name);
	FILE* fp = fopen(name, mode);
	fileOpenCheck(fp);
	return fp;
}
