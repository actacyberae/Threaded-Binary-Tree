#ifndef TBT_LIBRARY
#define TBT_LIBRARY

#include "./lib.h"

typedef struct node *TBTptr;

typedef unsigned char byte;

typedef struct node {
	int key;
	TBTptr left, right;
	byte lTag, rTag;
} TBTnode;

typedef struct TBT {
	int size;
	TBTptr root;
	TBTptr zero;
} TBT;

TBTptr prevTBTNode(TBTptr pNode);

TBTptr nextTBTNode(TBTptr pNode);

TBTptr getParentOfTBTNode(TBT *pTBT, TBTptr pNode);

TBTptr getInOrderTBTSuccessor(TBT *pTBT, TBTptr pNode);

TBTptr getInOrderTBTPredecessor(TBT *pTBT, TBTptr pNode);

TBTptr createTBT(TBT *pTBT, TBTptr *pRoot, TBTptr pNode, int pKey);

void insertTBTNodeInTBT(TBT *pTBT, int pKey);

void printTBT(TBT *pTBT);

void printTBTInOrderTraversal(TBT *pTBT, TBTptr pNode);

void freeTBT(TBT *pTBT);

TBTptr getTBTNodeInSubTBTByKey(TBT *pTBT, TBTptr pRoot, int pKey);

TBTptr getTBTNodeInTBTByKey(TBT *pTBT, int pKey);

TBTptr getMinimalTBTNodeInSubTBT(TBTptr pNode);

TBTptr getMinimalTBTNodeInTBT(TBT *pTBT);

TBTptr getMaximalTBTNodeInSubTBT(TBTptr pNode);

TBTptr getMaximalTBTNodeInTBT(TBT *pTBT);

void deleteTBTNodeFromTBT(TBT *pTBT, TBTptr pNode);

#endif
