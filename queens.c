#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <memory.h>
#include <stdlib.h>

typedef struct {
	char board[8][8];
	char queenCount;
} TNode;

void show_node(TNode *node)
{
	char i, j;

	for (i=0;i<8;i++)
	{
		for (j=0;j<8;j++)
			printf("%c", node->board[i][j] == 8 ? '*' : (node->board[i][j] == 0 ? ' ' : '.'));
		printf("\n");
	}
	printf("\n");
}

//{row, col}
char dir[8][2] = {{-1, 0}, {-1, +1}, {0, +1}, {+1, +1}, {+1, 0}, {+1, -1}, {0, -1}, {-1, -1}};

/*
state : {-1, +1}
*/
void set_queen(TNode *node, char row, char col, char state)
{
	char d, i, ncol, nrow;

	for (d = 0; d < 8; d++)
	{
		for (i = 1; i < 8; i++)
		{
			nrow = row + i * dir[d][0];
			ncol = col + i * dir[d][1];

			if (nrow < 0 || nrow > 7 || ncol < 0 || ncol > 7)
				break;

			node->board[nrow][ncol] += state;
		}
	}
	node->board[row][col] += state*8;
}

char find_empty(TNode *node, char col, char startRow)
{
	char i;

	for (i = startRow; i < 8; i++)
		if (node->board[i][col] == 0)
			return i;

	return -1;
}

TNode *find_solution(TNode *node)
{
	TNode *newNode, *result;
	char row, startRow = 0;

	printf("trying to place queen in column %d\n", (int)node->queenCount);

	if (node->queenCount == 8)
	{
		//return node;
		printf("solution found\n");
		return node;
	}

	do
	{
		printf("trying to find empty row starting from %d\n", (int)startRow);
		row = find_empty(node, node->queenCount, startRow);
		printf("row %d is empty\n", (int)row);
		if (row != -1)
		{
			newNode = (TNode*)malloc(sizeof(TNode));
			memcpy(newNode, node, sizeof(TNode));

			set_queen(newNode, row, newNode->queenCount, +1);
			newNode->queenCount++;

			show_node(newNode);

			result = find_solution(newNode);
			if (result != NULL)
				return result;
			startRow = row + 1;			
		}
	} while (row != -1);
	
	printf("cannot find solution from this node\n");
	return NULL;
}

void main(void)
{
	TNode *root;
	TNode *solution;

	root = (TNode*)malloc(sizeof(TNode));
	memset(root->board, 0, sizeof(root->board));
	root->queenCount = 0;


	show_node(root);
	solution = find_solution(root);
	if (solution != NULL)
		show_node(solution);
}
