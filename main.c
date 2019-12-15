#include <stdio.h>
#include <math.h>
#include "./libs/lib.h"
#include "./libs/TBT.h"

int main (int argc, char *argv[]) {
	TBT pTBT = {0, NULL};
	TBTptr pNode;
	
	insertTBTNodeInTBT(&pTBT, 40);
	insertTBTNodeInTBT(&pTBT, 30);
	insertTBTNodeInTBT(&pTBT, 35);
	insertTBTNodeInTBT(&pTBT, 31);
	insertTBTNodeInTBT(&pTBT, 34);
	insertTBTNodeInTBT(&pTBT, 33);
	insertTBTNodeInTBT(&pTBT, 25);
	insertTBTNodeInTBT(&pTBT, 1);
	insertTBTNodeInTBT(&pTBT, 27);
	insertTBTNodeInTBT(&pTBT, 26);
	insertTBTNodeInTBT(&pTBT, 28);
	insertTBTNodeInTBT(&pTBT, 60);
	insertTBTNodeInTBT(&pTBT, 50);
	insertTBTNodeInTBT(&pTBT, 47);
	insertTBTNodeInTBT(&pTBT, 55);
	insertTBTNodeInTBT(&pTBT, 57);
	insertTBTNodeInTBT(&pTBT, 52);
	insertTBTNodeInTBT(&pTBT, 54);
	insertTBTNodeInTBT(&pTBT, 53);
	insertTBTNodeInTBT(&pTBT, 70);
	insertTBTNodeInTBT(&pTBT, 65);
	insertTBTNodeInTBT(&pTBT, 75);
	printTBT(&pTBT);
	print_line(STDOUT_FILENO, "========\n");
	pNode = getTBTNodeInTBTByKey(&pTBT, 40);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d|%d|%d]\n", pNode->lTag, pNode->key, pNode->rTag);
	print_line(STDOUT_FILENO, "========\n");
	deleteTBTNodeFromTBT(&pTBT, pNode);
	printTBT(&pTBT);
	print_line(STDOUT_FILENO, "========\n");
	pNode = getTBTNodeInTBTByKey(&pTBT, 60);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d|%d|%d]\n", pNode->lTag, pNode->key, pNode->rTag);
	print_line(STDOUT_FILENO, "========\n");
	deleteTBTNodeFromTBT(&pTBT, pNode);
	printTBT(&pTBT);
	print_line(STDOUT_FILENO, "========\n");
	pNode = getTBTNodeInTBTByKey(&pTBT, 25);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d|%d|%d]\n", pNode->lTag, pNode->key, pNode->rTag);
	print_line(STDOUT_FILENO, "========\n");
	deleteTBTNodeFromTBT(&pTBT, pNode);
	printTBT(&pTBT);
	print_line(STDOUT_FILENO, "========\n");
	pNode = getTBTNodeInTBTByKey(&pTBT, 34);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d|%d|%d]\n", pNode->lTag, pNode->key, pNode->rTag);
	print_line(STDOUT_FILENO, "========\n");
	deleteTBTNodeFromTBT(&pTBT, pNode);
	printTBT(&pTBT);
	print_line(STDOUT_FILENO, "========\n");
	pNode = getTBTNodeInTBTByKey(&pTBT, 52);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d|%d|%d]\n", pNode->lTag, pNode->key, pNode->rTag);
	print_line(STDOUT_FILENO, "========\n");
	deleteTBTNodeFromTBT(&pTBT, pNode);
	printTBT(&pTBT);
	print_line(STDOUT_FILENO, "========\n");
	pNode = getTBTNodeInTBTByKey(&pTBT, 1);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d|%d|%d]\n", pNode->lTag, pNode->key, pNode->rTag);
	print_line(STDOUT_FILENO, "========\n");
	deleteTBTNodeFromTBT(&pTBT, pNode);
	printTBT(&pTBT);
	print_line(STDOUT_FILENO, "========\n");
	pNode = getTBTNodeInTBTByKey(&pTBT, 33);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d|%d|%d]\n", pNode->lTag, pNode->key, pNode->rTag);
	print_line(STDOUT_FILENO, "========\n");
	deleteTBTNodeFromTBT(&pTBT, pNode);
	printTBT(&pTBT);
	print_line(STDOUT_FILENO, "Exit\n");
	freeTBT(&pTBT);
	return 0;
}
