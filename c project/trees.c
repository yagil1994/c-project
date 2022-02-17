#pragma once
#include "trees.h"


static void AuxFreeTnode(treeNode* root);//check

treeNode* createTreeNode(imgPos position, treeNode** similar_neighbors)
{
	/*creates a treeNode*/
	treeNode* res;
	res = (treeNode*)malloc(sizeof(treeNode));
	checkAlloc(res);
	res->position[0] = position[0];
	res->position[1] = position[1];
	res->similar_neighbors = similar_neighbors;
	return res;
}

void AuxFreeTnode(treeNode* root)
{
	/*free a treeNode-it uses an Aux function that helps it*/
	int i = 0;
	while (root->similar_neighbors[i])
	{
		AuxFreeTnode(root->similar_neighbors[i]);
		i++;
	}
	free(root->similar_neighbors);
	free(root);
}

void FreeTnode(treeNode* root)
{
	/*free a treeNode helper*/
	if (root == NULL)
		return;
	AuxFreeTnode(root);
}

void FreeSegment(Segment* seg)
{
	/*free segment*/
	if (seg->root)
		FreeTnode(seg->root);
	free(seg);
}



void printTree(Segment tr)
{
	printTreeHelper(tr.root, 0);
}

void printTreeHelper(treeNode* root, int depth)
{
	for (int i = 0; i < depth; i++)
	{
		printf("    ");
	}
	printf("(%d,%d)->\n", root->position[0], root->position[1]);


	if (root->similar_neighbors[0] == NULL)
		return;
	else
	{
		depth++;
		for (int i = 0; root->similar_neighbors[i] != NULL; i++)
		{
			printTreeHelper(root->similar_neighbors[i], depth);
		}
	}
}

