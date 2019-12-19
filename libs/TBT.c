#include "./TBT.h"

TBTptr prevTBTNode(TBTptr pNode) {
	if (pNode->lTag == 0) {
		return pNode->left;
	}
	pNode = pNode->left;
	while (pNode->rTag != 0) {
		pNode = pNode->right;
	}
	return pNode;
}

TBTptr nextTBTNode(TBTptr pNode) {
	if (pNode->rTag == 0) {
		return pNode->right;
	}
	pNode = pNode->right;
	while (pNode->lTag != 0) {
		pNode = pNode->left;
	}
	return pNode;
}

TBTptr getParentOfTBTNode(TBT *pTBT, TBTptr pNode) {
	int pKey;
	TBTptr pParent;
	
	pKey = pNode->key;
	pParent = pTBT->root;
	while (pParent != (pTBT->zero)->right) {
		if (pParent->right == pNode || pParent->left == pNode) {
			return pParent;
		}
		if (pParent->key > pKey) {
			pParent = pParent->left;
		} else if (pParent->key < pKey) {
			pParent = pParent->right;
		} else {
			break;
		}
	}
	return pParent != (pTBT->zero)->right ? pParent : pNode;
}

TBTptr getInOrderTBTSuccessor(TBT *pTBT, TBTptr pNode) {
	int pKey;
	TBTptr pSuccessor;
	
	pKey = pNode->key;
	pNode = pTBT->root;
	while (pNode != (pTBT->zero)->right) {
		if (pNode->key > pKey) {
			pSuccessor = pNode;
			pNode = pNode->left;
		} else if (pNode->key < pKey) {
			pNode = pNode->right;
		} else {
			break;
		}
	}
	return pNode != (pTBT->zero)->right ? pSuccessor : (pTBT->zero)->right;
}

TBTptr getInOrderTBTPredecessor(TBT *pTBT, TBTptr pNode) {
	int pKey;
	TBTptr pPredecessor;
	
	pKey = pNode->key;
	pNode = pTBT->root;
	while (pNode != (pTBT->zero)->right) {
		if (pNode->key > pKey) {
			pNode = pNode->left;
		} else if (pNode->key < pKey) {
			pPredecessor = pNode;
			pNode = pNode->right;
		} else {
			break;
		}
	}
	return pNode != (pTBT->zero)->right ? pPredecessor : (pTBT->zero)->right;
}

static void threadingTBT(TBTptr pNode, TBTptr pParent, TBT *pTBT) {
	if (pNode == getMinimalTBTNodeInTBT(pTBT)) {
		pNode->left = (pTBT->zero)->left;
	} else {
		pNode->left = getInOrderTBTPredecessor(pTBT, pNode);
	}
	if (pNode == getMaximalTBTNodeInTBT(pTBT)) {
		pNode->right = (pTBT->zero)->right;
	} else {
		pNode->right = getInOrderTBTSuccessor(pTBT, pNode);
	}
}

static TBTptr createTBTNodeInTBT(TBTptr *pRoot, TBTptr pNode, int pKey) {
	pNode = *pRoot = (TBTptr) malloc(sizeof(TBTnode));
	pNode->key = pKey;
	pNode->lTag = pNode->rTag = 0;
	return pNode;
}

TBTptr createTBT(TBT *pTBT, TBTptr *pRoot, TBTptr pNode, int pKey) {
	pNode = createTBTNodeInTBT(pRoot, pNode, pKey);
	if (pTBT->zero == NULL) {
		pTBT->zero = malloc(sizeof(TBTnode));
		(pTBT->zero)->key = -1;
		(pTBT->zero)->lTag = 1;
		(pTBT->zero)->rTag = 1;
		(pTBT->zero)->left = pTBT->root;
		(pTBT->zero)->right = pTBT->zero;
	}
	pNode->right = (pTBT->zero)->right; 
	pNode->left = (pTBT->zero)->left;
	pTBT->size++;
	return pNode;
}

static void getVacancyPlaceForTBTNodeInTBT(TBT *pTBT, TBTptr *pRoot, TBTptr pNode, int pKey) {
	TBTptr pParent;
	
	if (pNode == NULL) {
		createTBT(pTBT, pRoot, pNode, pKey);
	} else {
		while (1) {
			if (pKey < pNode->key) {
				if (pNode->lTag == 0) {
					pParent = pNode;
					pParent->lTag = 1;
					pNode = createTBT(pTBT, &pNode->left, pNode->left, pKey);
					break;
				} else {
					pRoot = &pNode->left;
					pNode = pNode->left;
				}
			} else {
				if (pNode->rTag == 0) {
					pParent = pNode;
					pParent->rTag = 1;
					pNode = createTBT(pTBT, &pNode->right, pNode->right, pKey);
					break;
				} else {
					pRoot = &pNode->right;
					pNode = pNode->right;
				}
			}
		}
		threadingTBT(pNode, pParent, pTBT);
	}
}

void insertTBTNodeInTBT(TBT *pTBT, int pKey) {
	getVacancyPlaceForTBTNodeInTBT(pTBT, &pTBT->root, pTBT->root, pKey);
}

void printTBT(TBT *pTBT) {
	if (pTBT->zero != NULL) {
		printTBTInOrderTraversal(pTBT, pTBT->root);
	}
}

void printTBTInOrderTraversal(TBT *pTBT, TBTptr pNode) {
	TBTptr ptr;
	TBTptr prev;
	TBTptr next;
	
	ptr = pNode;
	while (ptr->lTag == 1) {
		ptr = ptr->left;
	}
	while (ptr != (pTBT->zero)->right) {
		print_line(STDOUT_FILENO, "[%d|%d|%d] ", ptr->lTag, ptr->key, ptr->rTag);
		print_line(STDOUT_FILENO, "[LC: %d] ", (ptr->left)->key);
		print_line(STDOUT_FILENO, "[RC: %d] ", (ptr->right)->key);
		prev = prevTBTNode(ptr);
		next = nextTBTNode(ptr);
		print_line(STDOUT_FILENO, "[prev: %d] ", prev->key);
		print_line(STDOUT_FILENO, "[next: %d] ", next->key);
		print_line(STDOUT_FILENO, "\n");
		ptr = nextTBTNode(ptr);
	}
}

void freeTBT(TBT *pTBT) {
	TBTptr ptr;
	TBTptr pParent;
	if (pTBT->zero != NULL) {
		ptr = getMinimalTBTNodeInTBT(pTBT);
		while (ptr != (pTBT->zero)->right) {
			pParent = ptr;
			ptr = nextTBTNode(ptr);
			free(pParent);
		}
		free(pTBT->zero);
	}
}

TBTptr getTBTNodeInSubTBTByKey(TBT *pTBT, TBTptr pRoot, int pKey) {
	pRoot = getMinimalTBTNodeInSubTBT(pRoot);
	while (pRoot != (pTBT->zero)->right) {
		if (pRoot->key == pKey) {
			break;
		}
		if (pRoot->key > pKey) {
			pRoot = pRoot->left;
		} else {
			pRoot = pRoot->right;
		}
	}
	return pRoot != (pTBT->zero)->right ? pRoot : (pTBT->zero)->right;
}

TBTptr getTBTNodeInTBTByKey(TBT *pTBT, int pKey) {
	return getTBTNodeInSubTBTByKey(pTBT, pTBT->root, pKey);
}

TBTptr getMinimalTBTNodeInSubTBT(TBTptr pNode) {
	while (pNode->lTag != 0) {
		pNode = pNode->left;
	}
	return pNode;
}

TBTptr getMinimalTBTNodeInTBT(TBT *pTBT) {
	return getMinimalTBTNodeInSubTBT(pTBT->root);
}

TBTptr getMaximalTBTNodeInSubTBT(TBTptr pNode) {
	while (pNode->rTag != 0) {
		pNode = pNode->right;
	}
	return pNode;
}

TBTptr getMaximalTBTNodeInTBT(TBT *pTBT) {
	return getMaximalTBTNodeInSubTBT(pTBT->root);
}

static void case_A(TBT *pTBT, TBTptr pDeletedNode, TBTptr pParentOfDeletedNode) {
	if (pDeletedNode != (pTBT->root)) {
		if (pParentOfDeletedNode->right == pDeletedNode) {
			pParentOfDeletedNode->right = pDeletedNode->right;
			pParentOfDeletedNode->rTag = 0;
		} else {
			pParentOfDeletedNode->left = pDeletedNode->left;
			pParentOfDeletedNode->lTag = 0;
		}
	} else {
		free(pTBT->zero);
		pTBT->zero = NULL;
	}
}

static void case_B(TBT *pTBT, TBTptr pDeletedNode, TBTptr pParentOfDeletedNode) {
	TBTptr pNewNode;
	TBTptr pMinimalNodeOfTree;
	TBTptr pMinimalNodeFromRightSubtreeOfDeletedNode;
	TBTptr pParentOfMinimalNodeFromRightSubtreeOfDeletedNode;
	TBTptr pMaximalNodeFromLeftSubtreeOfDeletedNode;
	
	if (pDeletedNode->lTag == 1) {
		pMaximalNodeFromLeftSubtreeOfDeletedNode = getMaximalTBTNodeInSubTBT(pDeletedNode->left);
		pNewNode = pDeletedNode->left;
		pMaximalNodeFromLeftSubtreeOfDeletedNode->right = pDeletedNode->right;
	} else {
		pMinimalNodeFromRightSubtreeOfDeletedNode = getMinimalTBTNodeInSubTBT(pDeletedNode->right);
		pNewNode = pDeletedNode->right;
		pMinimalNodeFromRightSubtreeOfDeletedNode->left = pDeletedNode->left;
	}
	if (pDeletedNode != (pTBT->root)) {
		if (pParentOfDeletedNode->right == pDeletedNode) {
			pParentOfDeletedNode->right = pNewNode;
		} else {
			pParentOfDeletedNode->left = pNewNode;
		}
	} else {
		pMinimalNodeOfTree = getMinimalTBTNodeInTBT(pTBT);
		pMinimalNodeOfTree->left = pNewNode;
		(pTBT->zero)->left = pNewNode;
		(pTBT->root) = pNewNode;
		(pTBT->zero)->right = pTBT->zero;
	}
}

static void case_C(TBT *pTBT, TBTptr pDeletedNode, TBTptr pParentOfDeletedNode) {
	TBTptr pMinimalNodeOfTree;
	TBTptr pMinimalNodeFromRightSubtreeOfDeletedNode;
	TBTptr pParentOfMinimalNodeFromRightSubtreeOfDeletedNode;
	TBTptr pMaximalNodeFromLeftSubtreeOfDeletedNode;
	
	pMinimalNodeFromRightSubtreeOfDeletedNode = getMinimalTBTNodeInSubTBT(pDeletedNode->right);
	pParentOfMinimalNodeFromRightSubtreeOfDeletedNode = getParentOfTBTNode(pTBT, pMinimalNodeFromRightSubtreeOfDeletedNode);
	if (pParentOfMinimalNodeFromRightSubtreeOfDeletedNode != pDeletedNode) {
		pParentOfMinimalNodeFromRightSubtreeOfDeletedNode->left = pMinimalNodeFromRightSubtreeOfDeletedNode->right;
		pParentOfMinimalNodeFromRightSubtreeOfDeletedNode->lTag = pMinimalNodeFromRightSubtreeOfDeletedNode->rTag;
	}
	pMaximalNodeFromLeftSubtreeOfDeletedNode = getMaximalTBTNodeInSubTBT(pDeletedNode->left);
	pMaximalNodeFromLeftSubtreeOfDeletedNode->right = pMinimalNodeFromRightSubtreeOfDeletedNode;
	
	if (pMinimalNodeFromRightSubtreeOfDeletedNode != pDeletedNode->right) {
		pMinimalNodeFromRightSubtreeOfDeletedNode->right = pDeletedNode->right;
		pMinimalNodeFromRightSubtreeOfDeletedNode->rTag = pDeletedNode->rTag;
	}
	pMinimalNodeFromRightSubtreeOfDeletedNode->left = pDeletedNode->left;
	pMinimalNodeFromRightSubtreeOfDeletedNode->lTag = pDeletedNode->lTag;
	if (pDeletedNode != (pTBT->root)) {
		if (pParentOfDeletedNode->right == pDeletedNode) {
			pParentOfDeletedNode->right = pMinimalNodeFromRightSubtreeOfDeletedNode;
		} else {
			pParentOfDeletedNode->left = pMinimalNodeFromRightSubtreeOfDeletedNode;
		}
	} else {
		pMinimalNodeOfTree = getMinimalTBTNodeInTBT(pTBT);
		pMinimalNodeOfTree->left = pMinimalNodeFromRightSubtreeOfDeletedNode;
		(pTBT->zero)->left = pMinimalNodeFromRightSubtreeOfDeletedNode;
		(pTBT->root) = pMinimalNodeFromRightSubtreeOfDeletedNode;
		(pTBT->zero)->right = pTBT->zero;
	}
}

void deleteTBTNodeFromTBT(TBT *pTBT, TBTptr pNode) {
	TBTptr pParent;
	
	if (pNode != pTBT->zero) {
		pTBT->size--;
		pParent = getParentOfTBTNode(pTBT, pNode);
		if ((pNode->rTag == 0) && (pNode->lTag == 0)) {
			case_A(pTBT, pNode, pParent);
		} else if ((pNode->rTag == 0) || (pNode->lTag == 0)) {
			case_B(pTBT, pNode, pParent);
		} else {
			case_C(pTBT, pNode, pParent);
		}
		free(pNode);
	}
}
