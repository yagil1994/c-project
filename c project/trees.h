
#ifndef TREES_H
#define TREES_H

#include "image.h"

/************typedefs**************/
/*children array*/
typedef struct _treeNode
{
	imgPos position;
	struct _treeNode** similar_neighbors;
}treeNode;

/*the total number of tree nodes*/
typedef struct _segment
{
	treeNode* root;
	unsigned int size;
}Segment;


/************declarations**************/

/*
creates a treeNode
*/
treeNode* createTreeNode(imgPos position, treeNode** similar_neighbors);

/*
free a treeNode-it uses an Aux function that helps it
*/
void FreeTnode(treeNode* root);

/*
free segment
*/
void FreeSegment(Segment* seg);	

/*
for testing purposes
*/
void printTree(Segment tr);
void printTreeHelper(treeNode* root, int depth);

#endif TREES_H
