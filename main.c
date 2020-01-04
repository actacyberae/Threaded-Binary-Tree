#include <stdio.h>
#include <math.h>
#include "./libs/lib.h"
#include "./libs/TBT.h"

int main (int argc, char *argv[]) {
	TBT pTBT = {0, NULL};
	TBTptr pNode;
	Insert_node(&pTBT, 40);
	Insert_node(&pTBT, 30);
	Insert_node(&pTBT, 35);
	Insert_node(&pTBT, 34);
	Insert_node(&pTBT, 32);
	Insert_node(&pTBT, 25);
	Insert_node(&pTBT, 1);
	Insert_node(&pTBT, 27);
	Insert_node(&pTBT, 26);
	Insert_node(&pTBT, 28);
	Insert_node(&pTBT, 60);
	Insert_node(&pTBT, 50);
	Insert_node(&pTBT, 47);
	Insert_node(&pTBT, 55);
	Insert_node(&pTBT, 57);
	Insert_node(&pTBT, 52);
	Insert_node(&pTBT, 54);
	Insert_node(&pTBT, 53);
	Insert_node(&pTBT, 70);
	Insert_node(&pTBT, 65);
	Insert_node(&pTBT, 75);
	tree_info(&pTBT);
	
	print_line(STDOUT_FILENO, "========\n");
	Get_node(&pTBT, 70, &pNode);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	Free_node(&pTBT, pNode);
	tree_info(&pTBT);
	
	print_line(STDOUT_FILENO, "========\n");
	Get_node(&pTBT, 75, &pNode);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	Free_node(&pTBT, pNode);
	tree_info(&pTBT);
	
	print_line(STDOUT_FILENO, "========\n");
	Get_node(&pTBT, 65, &pNode);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	Free_node(&pTBT, pNode);
	tree_info(&pTBT);
	
	print_line(STDOUT_FILENO, "========\n");
	Get_node(&pTBT, 34, &pNode);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	Free_node(&pTBT, pNode);
	tree_info(&pTBT);
	
	print_line(STDOUT_FILENO, "========\n");
	Get_node(&pTBT, 32, &pNode);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	Free_node(&pTBT, pNode);
	tree_info(&pTBT);
	
	print_line(STDOUT_FILENO, "========\n");
	Get_node(&pTBT, 1, &pNode);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	Free_node(&pTBT, pNode);
	tree_info(&pTBT);
	
	print_line(STDOUT_FILENO, "========\n");
	Get_node(&pTBT, 40, &pNode);
	print_line(STDOUT_FILENO, "DELETE NODE: [%d]\n", pNode->key);
	print_line(STDOUT_FILENO, "========\n");
	Free_node(&pTBT, pNode);
	tree_info(&pTBT);
	
	print_line(STDOUT_FILENO, "====33====\n");
	Get_node(&pTBT, 33, &pNode);
	print_line(STDOUT_FILENO, "====33====\n");
	Free_node(&pTBT, pNode);
	tree_info(&pTBT);
	
	Free_tree(&pTBT);
	print_line(STDOUT_FILENO, "Exit\n");
	return 0;
}
