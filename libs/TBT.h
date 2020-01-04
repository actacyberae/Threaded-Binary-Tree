#ifndef TBT_LIBRARY
#define TBT_LIBRARY

#include "./lib.h"

#define ER_EMPTYTREE -1
#define ER_EMPTYNODE -2
#define ER_UNKNWPRNT -3

#define TRUE 1
#define FALSE 0

typedef struct node *TBTptr;

typedef unsigned char TByte;

typedef struct node {
	int key;
	TByte lTag, rTag;
	TBTptr left, right;
} TBTnode;

typedef struct TBT {
	int size;
	TBTptr root;
	TBTptr zero;
} TBT;

void Insert_node(TBT *pTBT, int pKey);

void tree_info(TBT *pTBT);

void Free_tree(TBT *pTBT);

void Free_node(TBT *pTBT, TBTptr pNode);

void Get_node(TBT *pTBT, int pKey, TBTptr *pNode);

#endif
