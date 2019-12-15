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

TBTptr getInOrderTBTSuccessor(TBT *pTBT, TBTptr pNode);

TBTptr getInOrderTBTPredecessor(TBT *pTBT, TBTptr pNode);

void insertTBTNodeInTBT(TBT *pTBT, int pKey);

void getVacancyPlaceForTBTNodeInTBT(TBT *pTBT, TBTptr *pRoot, TBTptr pNode, int pKey);

TBTptr createTBTNodeInTBT(TBTptr *pRoot, TBTptr pNode, int pKey);

TBTptr createTBT(TBT *pTBT, TBTptr *pRoot, TBTptr pNode, int pKey);

void printTBT(TBT *pTBT);

void printTBTInOrderTraversal(TBT *pTBT, TBTptr pNode);

void freeTBT(TBT *pTBT);

TBTptr getTBTNodeInSubTBTByKey(TBT *pTBT, TBTptr pNode, int pKey);

TBTptr getTBTNodeInTBTByKey(TBT *pTBT, int pKey);

TBTptr getMinimalTBTNodeInSubTBT(TBTptr pNode);

TBTptr getMaximalTBTNodeInSubTBT(TBTptr pNode);

TBTptr getMinimalTBTNodeInTBT(TBT *pTBT);

TBTptr getMaximalTBTNodeInTBT(TBT *pTBT);

TBTptr getParentOfTBTNode(TBT *pTBT, TBTptr pNode);

void deleteTBTNodeFromTBT(TBT *pTBT, TBTptr pNode);

#endif
