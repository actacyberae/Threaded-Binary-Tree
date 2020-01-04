#include "./TBT.h"

/*
*
*/
static int get_previous_node(TBTptr *pNode) {
	if (*pNode == NULL) {
		return ER_EMPTYNODE;
	}
	if ((*pNode)->lTag == 0) {
		*pNode = (*pNode)->left;
		return TRUE;
	}
	*pNode = (*pNode)->left;
	while ((*pNode)->rTag != 0) {
		*pNode = (*pNode)->right;
	}
	return TRUE;
}

static void Get_previous_node(TBTptr *pNode) {
	int RETURN;
	
	RETURN = get_previous_node(pNode);
	switch (RETURN) {
		case ER_EMPTYNODE:
			err_msg("get_previous_node: ER_EMPTYNODE\n");
			exit(EXIT_FAILURE);
	}
}

/*
*
*/
static int get_next_node(TBTptr *pNode) {
	if (*pNode == NULL) {
		return ER_EMPTYNODE;
	}
	if ((*pNode)->rTag == 0) {
		*pNode = (*pNode)->right;
		return TRUE;
	}
	*pNode = (*pNode)->right;
	while ((*pNode)->lTag != 0) {
		*pNode = (*pNode)->left;
	}
	return TRUE;
}

static void Get_next_node(TBTptr *pNode) {
	int RETURN;
	
	RETURN = get_next_node(pNode);
	switch (RETURN) {
		case ER_EMPTYNODE:
			err_msg("get_next_node: ER_EMPTYNODE\n");
			exit(EXIT_FAILURE);
	}
}

/*
* Простая функция распечатки информации об узле pNode: ключе, левом и пр
* авом показателе типе связи. Если показатель типа равен 1, то связь явл
* яется нитью. В противном случае - связью дочернего и родительского узл
* ов. Формат информации следующий:
* [КЛП|(ПЛН)КВ(ППН)|КПП], где
* КЛП - ключ левого потомка
* КПП - ключ правого потомка
* КВ  - ключ вершины
* ПЛН - показатель типа левой вершины
* ППН - показатель типа правой вершины
* Если потомок у вершины отсутствует, то вместо информации о потомке, пи
* шется слово NULL.
*/
void node_info(TBTptr pNode) {
	print_line(STDOUT_FILENO, "[");
	if (pNode != NULL) {
		if (pNode->left != NULL) {
			print_line(STDOUT_FILENO, "%d|", (pNode->left)->key);
		} else {
			print_line(STDOUT_FILENO, "NULL|");
		}
		print_line(STDOUT_FILENO, "(%d)%d(%d)", pNode->lTag, pNode->key, pNode->rTag);
			if (pNode->right != NULL) {
			print_line(STDOUT_FILENO, "|%d", (pNode->right)->key);
		} else {
			print_line(STDOUT_FILENO, "|NULL");
		}
	} else {
		print_line(STDOUT_FILENO, "NULL");
	}
	print_line(STDOUT_FILENO, "]\n");
}

/*
* Обобщенная функция печати дерева pTBT. В качестве входящего параметра 
* рекурсивной функции печати выступает корень дерева pTBT. Т. о., дерево
* обходится в порядке симметричного обхода и последовательно распечатыва
* ется вся информация об узлах.
*/
void tree_info(TBT *pTBT) {
	TBTptr ptr;
	
	if (pTBT->zero != NULL) {
		ptr = pTBT->root;
		while (ptr->lTag == 1) {
			ptr = ptr->left;
		}
		while (ptr != (pTBT->zero)->right) {
			node_info(ptr);
			get_next_node(&ptr);
		}
	}
}

/*
* Функция возвращает родителя вершины pNode дерева pTBT. В случае, если 
* берется корень дерева pTBT, то возвращается само корневое значение. Пу
* сть корень поддерева обозначается буквой A, а его левый и правый потом
* ки B и C соответственно. Данные сохраняются в pParent по значению.
*      |
*      A
*     / \
*    /   \
*   B     C
* Тогда вызов функции get_parent_of_node для узла C вернет вершину A.
*/
static int get_parent_of_node(TBT *pTBT, TBTptr pNode, TBTptr *pParent) {
	int pKey;
	
	if (pTBT == NULL) {
		return ER_EMPTYTREE;
	}
	if (pNode == NULL) {
		return ER_EMPTYNODE;
	}
	pKey = pNode->key;
	*pParent = pTBT->root;
	while (*pParent != (pTBT->zero)->right) {
		if ((*pParent)->right == pNode || (*pParent)->left == pNode) {
			return TRUE;
		}
		if ((*pParent)->key > pKey) {
			*pParent = (*pParent)->left;
		} else if ((*pParent)->key < pKey) {
			*pParent = (*pParent)->right;
		} else {
			break;
		}
	}
	*pParent != (pTBT->zero)->right ? *pParent : pNode;
	return TRUE;
}

static void Get_parent_of_node(TBT *pTBT, TBTptr pNode, TBTptr *pParent) {
	int RETURN;
	
	RETURN = get_parent_of_node(pTBT, pNode, pParent);
	switch (RETURN) {
		case ER_EMPTYTREE:
			err_msg("get_parent_of_node: ER_EMPTYTREE\n");
			exit(EXIT_FAILURE);
		case ER_EMPTYNODE:
			err_msg("get_parent_of_node: ER_EMPTYNODE\n");
			exit(EXIT_FAILURE);
	}
}

/*
*
*/
static int get_in_order_successor(TBT *pTBT, TBTptr pNode, TBTptr *pSuccessor) {
	int pKey;
	
	if (pTBT == NULL) {
		return ER_EMPTYTREE;
	}
	if (pNode == NULL) {
		return ER_EMPTYNODE;
	}
	pKey = pNode->key;
	pNode = pTBT->root;
	while (pNode != (pTBT->zero)->right) {
		if (pNode->key > pKey) {
			*pSuccessor = pNode;
			pNode = pNode->left;
		} else if (pNode->key < pKey) {
			pNode = pNode->right;
		} else {
			break;
		}
	}
	pNode != (pTBT->zero)->right ? *pSuccessor : (pTBT->zero)->right;
	return TRUE;
}

static void Get_in_order_successor(TBT *pTBT, TBTptr pNode, TBTptr *pSuccessor) {
	int RETURN;
	
	RETURN = get_in_order_successor(pTBT, pNode, pSuccessor);
	switch (RETURN) {
		case ER_EMPTYTREE:
			err_msg("get_in_order_successor: ER_EMPTYTREE\n");
			exit(EXIT_FAILURE);
		case ER_EMPTYNODE:
			err_msg("get_in_order_successor: ER_EMPTYNODE\n");
			exit(EXIT_FAILURE);
	}
}

/*
*
*/
static int get_in_order_predecessor(TBT *pTBT, TBTptr pNode, TBTptr *pPredecessor) {
	int pKey;
	
	if (pTBT == NULL) {
		return ER_EMPTYTREE;
	}
	if (pNode == NULL) {
		return ER_EMPTYNODE;
	}
	pKey = pNode->key;
	pNode = pTBT->root;
	while (pNode != (pTBT->zero)->right) {
		if (pNode->key > pKey) {
			pNode = pNode->left;
		} else if (pNode->key < pKey) {
			*pPredecessor = pNode;
			pNode = pNode->right;
		} else {
			break;
		}
	}
	pNode != (pTBT->zero)->right ? *pPredecessor : (pTBT->zero)->right;
	return TRUE;
}

static void Get_in_order_predecessor(TBT *pTBT, TBTptr pNode, TBTptr *pPredecessor) {
	int RETURN;
	
	RETURN = get_in_order_predecessor(pTBT, pNode, pPredecessor);
	switch (RETURN) {
		case ER_EMPTYTREE:
			err_msg("get_in_order_predecessor: ER_EMPTYTREE\n");
			exit(EXIT_FAILURE);
		case ER_EMPTYNODE:
			err_msg("get_in_order_predecessor: ER_EMPTYNODE\n");
			exit(EXIT_FAILURE);
	}
}

/*
* Функция возвращает вершину с минимальным ключом в поддереве с корнем в
* A. Архитектура дерева такова, что минимальная вершина всегда будет леж
* ать слева от корня. Для дерева приведенного ниже, такой вершиной будет
* узел B.
*      |
*      A
*     / \
*    /   \
*   B     C
*/
static int get_minimal_node(TBTptr pRoot, TBTptr *pMinimalNode) {
	if (pRoot == NULL) {
		return ER_EMPTYNODE;
	}
	*pMinimalNode = pRoot;
	while ((*pMinimalNode)->lTag != 0) {
		*pMinimalNode = (*pMinimalNode)->left;
	}
	return TRUE;
}

static void Get_minimal_node(TBTptr pRoot, TBTptr *pMinimalNode) {
	int RETURN;
	
	RETURN = get_minimal_node(pRoot, pMinimalNode);
	switch (RETURN) {
		case ER_EMPTYNODE:
			err_msg("get_minimal_node: ER_EMPTYNODE\n");
			exit(EXIT_FAILURE);
	}
}

/*
* Функция возвращает вершину с минимальным ключом в поддереве с корнем в
* A. Архитектура дерева такова, что минимальная вершина всегда будет леж
* ать слева от корня. Для дерева приведенного ниже, такой вершиной будет
* узел B.
*      |
*      A
*     / \
*    /   \
*   B     C
*/
static int get_maximal_node(TBTptr pRoot, TBTptr *pMaximalNode) {
	if (pRoot == NULL) {
		return ER_EMPTYNODE;
	}
	*pMaximalNode = pRoot;
	while ((*pMaximalNode)->rTag != 0) {
		*pMaximalNode = (*pMaximalNode)->right;
	}
	return TRUE;
}

static void Get_maximal_node(TBTptr pRoot, TBTptr *pMaximalNode) {
	int RETURN;
	
	RETURN = get_maximal_node(pRoot, pMaximalNode);
	switch (RETURN) {
		case ER_EMPTYNODE:
			err_msg("get_maximal_node: ER_EMPTYNODE\n");
			exit(EXIT_FAILURE);
	}
}

/*
*
*/
static void tree_threading(TBT *pTBT, TBTptr pNode, TBTptr pParent) {
	TBTptr pMinimalNode;
	TBTptr pMaximalNode;
	
	Get_minimal_node(pTBT->root, &pMinimalNode);
	Get_maximal_node(pTBT->root, &pMaximalNode);
	if (pNode == pMinimalNode) {
		pNode->left = (pTBT->zero)->left;
	} else {
		Get_in_order_predecessor(pTBT, pNode, &(pNode->left));
	}
	if (pNode == pMaximalNode) {
		pNode->right = (pTBT->zero)->right;
	} else {
		Get_in_order_successor(pTBT, pNode, &(pNode->right));
	}
}

/*
* 
*/
static void declare_a_new_node(TBT *pTBT, TBTptr *pRoot, TBTptr *pNode, int pKey) {
	*pNode = *pRoot = (TBTptr) Malloc(sizeof(TBTnode));
	(*pNode)->key = pKey;
	(*pNode)->left = (*pNode)->right = NULL;
	(*pNode)->lTag = (*pNode)->rTag = 0;
	pTBT->size++;
	if (pTBT->zero == NULL) {
		pTBT->zero = malloc(sizeof(TBTnode));
		(pTBT->zero)->key = -1;
		(pTBT->zero)->lTag = 1;
		(pTBT->zero)->rTag = 1;
		(pTBT->zero)->left = pTBT->root;
		(pTBT->zero)->right = pTBT->zero;
	}
	(*pNode)->right = (pTBT->zero)->right; 
	(*pNode)->left = (pTBT->zero)->left;
	pTBT->size++;
}

/*
* 
*/
static void insert_node(TBT *pTBT, TBTptr *pRoot, TBTptr pNode, int pKey) {
	TBTptr pParent;
	
	if (pNode == NULL) {
		declare_a_new_node(pTBT, pRoot, &pNode, pKey);
	} else {
		while (TRUE) {
			if (pKey < pNode->key) {
				if (pNode->lTag == FALSE) {
					pParent = pNode;
					pParent->lTag = TRUE;
					declare_a_new_node(pTBT, &pNode->left, &pNode, pKey);
					break;
				} else {
					pRoot = &pNode->left;
					pNode = pNode->left;
				}
			} else {
				if (pNode->rTag == FALSE) {
					pParent = pNode;
					pParent->rTag = TRUE;
					declare_a_new_node(pTBT, &pNode->right, &pNode, pKey);
					break;
				} else {
					pRoot = &pNode->right;
					pNode = pNode->right;
				}
			}
		}
		tree_threading(pTBT, pNode, pParent);
	}
}


void Insert_node(TBT *pTBT, int pKey) {
	insert_node(pTBT, &pTBT->root, pTBT->root, pKey);
}

/*
* Не совсем эффективный, но все же способ получения узла по ключу pKey.
*/
static int get_node(TBT *pTBT, int pKey, TBTptr *pNode) {
	TBTptr pMaximalNode;
	
	if (pTBT == NULL) {
		return ER_EMPTYTREE;
	}
	Get_minimal_node(pTBT->root, pNode);
	Get_maximal_node(pTBT->root, &pMaximalNode);
	while (*pNode != pMaximalNode) {
		if ((*pNode)->key >= pKey) {
			break;
		}
		Get_next_node(pNode);
	}
	if ((*pNode)->key != pKey) {
		*pNode = NULL;
		return ER_EMPTYNODE;
	}
	return TRUE;
}

void Get_node(TBT *pTBT, int pKey, TBTptr *pNode) {
	int RETURN;
	
	RETURN = get_node(pTBT, pKey, pNode);
	switch (RETURN) {
		case ER_EMPTYTREE:
			err_msg("get_node: ER_EMPTYTREE\n");
		case ER_EMPTYNODE:
			err_msg("get_node: ER_EMPTYNODE\n");
	}
}

/*
* Функция проверки на то, что узел pNode является левым, либо правым пот
* омком в узла pParent. Если pParent не является родителем pNode, то фун
* кция возвращает отрицательное значение.
*/
static int is_node_a_left_child(TBTptr pNode, TBTptr pParent) {
	if (pNode == NULL || pParent == NULL) {
		return ER_EMPTYNODE;
	}
	if (pParent->left == pNode) {
		return TRUE;
	} else if (pParent->right == pNode) {
		return FALSE;
	} else {
		return ER_UNKNWPRNT;
	} 
}

static int Is_node_a_left_child(TBTptr pNode, TBTptr pParent) {
	int RETURN;
	
	RETURN = is_node_a_left_child(pNode, pParent);
	switch (RETURN) {
		case ER_EMPTYNODE:
			err_msg("is_node_a_left_child: ER_EMPTYNODE\n");
			exit(EXIT_FAILURE);
		case ER_UNKNWPRNT:
			err_msg("is_node_a_left_child: ER_UNKNWPRNT\n");
			exit(EXIT_FAILURE);
		default:
			return RETURN;
	}
}

/*
* Заменяет поддерево с корнем в узле pNode поддеревом с корнем в узле   
* pNewNode. Родителю узла pNode устанавливается новый левый или правый п
* отомок. Если содержимое дерева заменяется полностью, то корень pTBT пр
* инимает новое значение корневого узла pNewNode.                       
*/
static int transplant(TBT *pTBT, TBTptr pNode, TBTptr pNewNode) {
	TBTptr pParent;
	TBTptr pMinimalNode;
	TBTptr pMaximalNode;
	
	if (pTBT == NULL) {
		return ER_EMPTYTREE;
	}
	if (pNode == NULL) {
		return ER_EMPTYNODE;
	}
	if (pNode != pTBT->root) {
		Get_parent_of_node(pTBT, pNode, &pParent);
		if (pParent->right == pNode) {
			if (pNewNode == NULL) {
				pParent->rTag = 0;
				pParent->right = pNode->right;
			} else {
				pParent->right = pNewNode;
			}
		} else {
			if (pNewNode == NULL) {
				pParent->lTag = 0;
				pParent->left = pNode->left;
			} else {
				pParent->left = pNewNode;
			}
		}
	} else {
		if (pNewNode != NULL) {
			Get_minimal_node(pTBT->root, &pMinimalNode);
			pMinimalNode->left = pNewNode;
			(pTBT->zero)->left = pNewNode;
			(pTBT->root) = pNewNode;
			(pTBT->zero)->right = pTBT->zero;
		} else {
			free(pTBT->zero);
			pTBT->zero = NULL;
		}
	}
	return TRUE;
}

static void Transplant(TBT *pTBT, TBTptr pNode, TBTptr pNewNode) {
	int RETURN;
	
	RETURN = transplant(pTBT, pNode, pNewNode);
	switch (RETURN) {
		case ER_EMPTYTREE:
			err_msg("transplant: ER_EMPTYTREE\n");
			exit(EXIT_FAILURE);
		case ER_EMPTYNODE:
			err_msg("transplant: ER_EMPTYNODE\n");
			exit(EXIT_FAILURE);
	}
}

/*
* Случай, когда удаляется лист дерева.
*/
static void case_A(TBT *pTBT, TBTptr *pDeletedNode) {
	Transplant(pTBT, *pDeletedNode, NULL);
}

/*
* Случай, когда удаляется вершина дерева с одним потомком.
*/
static void case_B(TBT *pTBT, TBTptr *pDeletedNode) {
	TBTptr pNewNode;
	TBTptr pMinimalNode;
	TBTptr pMaximalNode;
	
	if ((*pDeletedNode)->lTag == 1) {
		Get_maximal_node((*pDeletedNode)->left, &pMaximalNode);
		pNewNode = (*pDeletedNode)->left;
		pMaximalNode->right = (*pDeletedNode)->right;
	} else {
		Get_minimal_node((*pDeletedNode)->right, &pMinimalNode);
		pNewNode = (*pDeletedNode)->right;
		pMinimalNode->left = (*pDeletedNode)->left;
	}
	Transplant(pTBT, *pDeletedNode, pNewNode);
}

/*
* Случай, когда удаляется вершина дерева с двумя потомками.
*/
static void case_C(TBT *pTBT, TBTptr *pDeletedNode) {
	TBTptr pMinimalNodeFromRightSubtreeOfDeletedNode;
	TBTptr pMaximalNodeFromLeftSubtreeOfDeletedNode;
	TBTptr pParentOfMinimalNodeFromRightSubtreeOfDeletedNode;
	
	Get_minimal_node((*pDeletedNode)->right, &pMinimalNodeFromRightSubtreeOfDeletedNode);
	Get_parent_of_node(pTBT, pMinimalNodeFromRightSubtreeOfDeletedNode, &pParentOfMinimalNodeFromRightSubtreeOfDeletedNode);
	if (pParentOfMinimalNodeFromRightSubtreeOfDeletedNode != *pDeletedNode) {
		pParentOfMinimalNodeFromRightSubtreeOfDeletedNode->left = pMinimalNodeFromRightSubtreeOfDeletedNode->right;
		pParentOfMinimalNodeFromRightSubtreeOfDeletedNode->lTag = pMinimalNodeFromRightSubtreeOfDeletedNode->rTag;
	}
	Get_maximal_node((*pDeletedNode)->left, &pMaximalNodeFromLeftSubtreeOfDeletedNode);
	pMaximalNodeFromLeftSubtreeOfDeletedNode->right = pMinimalNodeFromRightSubtreeOfDeletedNode;
	if (pMinimalNodeFromRightSubtreeOfDeletedNode != (*pDeletedNode)->right) {
		pMinimalNodeFromRightSubtreeOfDeletedNode->right = (*pDeletedNode)->right;
		pMinimalNodeFromRightSubtreeOfDeletedNode->rTag = (*pDeletedNode)->rTag;
	}
	pMinimalNodeFromRightSubtreeOfDeletedNode->left = (*pDeletedNode)->left;
	pMinimalNodeFromRightSubtreeOfDeletedNode->lTag = (*pDeletedNode)->lTag;
	Transplant(pTBT, *pDeletedNode, pMinimalNodeFromRightSubtreeOfDeletedNode);
}

static int free_node(TBT *pTBT, TBTptr pNode) {
	if (pTBT == NULL) {
		return ER_EMPTYTREE;
	}
	if (pNode == NULL) {
		return ER_EMPTYNODE;
	}
	pTBT->size--;
	if (pNode->rTag == 0 && pNode->lTag == 0) {
		case_A(pTBT, &pNode);
	} else if (pNode->rTag == 0 || pNode->lTag == 0) {
		case_B(pTBT, &pNode);
	} else {
		case_C(pTBT, &pNode);
	}
	free(pNode);
	return TRUE;
}

void Free_node(TBT *pTBT, TBTptr pNode) {
	int RETURN;
	
	RETURN = free_node(pTBT, pNode);
	switch (RETURN) {
		case ER_EMPTYTREE:
			err_msg("free_node: ER_EMPTYTREE\n");
			exit(EXIT_FAILURE);
		case ER_EMPTYNODE:
			err_msg("free_node: ER_EMPTYNODE\n");
	}
}

/*
* Рекурсивная функция free_tree помещает выделенную память под узел дере
* ва в список повторно используемых областей. Указатель pNode может быть
* равным NULL и проверка, используемая внутри функции указателя, использ
* уется для  последовательное перемещения по поддереву с корнем в pRoot 
* в порядке левого обхода.
*/
static int free_tree(TBT *pTBT) {
	TBTptr pNode;
	TBTptr pDeletedNode;
	TBTptr pMaximalNode;
	
	if (pTBT == NULL) {
		return ER_EMPTYTREE;
	}
	Get_minimal_node(pTBT->root, &pNode);
	Get_maximal_node(pTBT->root, &pMaximalNode);
	while (pNode != pMaximalNode) {
		pDeletedNode = pNode;
		Get_next_node(&pNode);
		free(pDeletedNode);
	}
	free(pNode);
	free(pTBT->zero);
	return TRUE;
}

/*
* Для очистки всего дерева pTBT используется функция Free_tree, которая 
* задействует рекурсивную функцию free_tree, в качестве параметра которо
* й передает корень дерева pTBT->root.
*/
void Free_tree(TBT *pTBT) {
	int RETURN;
	
	RETURN = free_tree(pTBT);
	switch (RETURN) {
		case ER_EMPTYTREE:
			err_msg("free_node: ER_EMPTYTREE\n");
	}
}
