#ifndef SERVICE_FUNCS_H
#define SERVICE_FUNCS_H


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Uchar unsigned char
#define Uint unsigned int
#define Ushort unsigned short int

typedef char BOOL;
typedef Uchar BYTE;

#define TRUE 1
#define FALSE 0
#define SPACE ' '
#define NULLCHAR '\0'
#define NEWLINE '\n'
#define TAB '\t'

#define ISSPACE(c) ((c)==SPACE)
#define ISWHITESPACE(c) (((c)==SPACE)||((c)==NEWLINE)||((c)==TAB))
#define ISNUMBER(c) (((c)>='0') && ((c)<='9'))
#define ALLOCATION_ERROR 1
#define COMPATIBILITY_ERROR 2
#define FILE_OPEN_ERROR 3
#define FILE_NAME_ERROR 4
#define INVALID_DATA_IN_FILE 5
#define EMPTY_PGM_FILE 6

#define BITS_IN_BYTE 8

/*
check a dynamically allocated variable
*/
void checkAlloc(void* ptr);

/*
check if a file has been opened successfuly
*/
void fileOpenCheck(FILE* fname);

/*
check if a given file name string is not NULL
*/
void fileNameCheck(char* fname);


/*
allocate a char array with size, return the allocated array
will add +1 for the '\0' to the received size
*/
char* allocateString(int size);

/*
get a file name, it's current format, the desired new format
create a new file name with the new format instead of the old one
*/
char* replaceFileFormat(char* fname, char* currFormat, char* newFormat);
/*
given a base number and a power number,
calculate the power of that base.
*/
int power(int base, int pow);

/*
replaces 3 lines of code
checks if a given file name string is not null
then opens the file
checks if file opened succesfully
returns a file pointer
*/
FILE* fileOpenProcedure(char* name, char* mode);

#endif SERVICE_FUNCS_H