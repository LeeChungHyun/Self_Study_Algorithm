#include "BinaryTree.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

void Create(BinaryTree* binaryTree) {
	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

BinaryNode* Insert(BinaryTree* binaryTree, void* key, size_t size, int(*compare)(void*, void*)) {
	BinaryNode* index;
	BinaryNode* parent = NULL;
	index = binaryTree->root;
	//부모 노드 지정
	while (index != NULL) {
		parent = index;
		if (compare(index + 1, key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	//자식노드 할당
	index = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
	memcpy(index + 1, key, size);
	index->left = NULL;
	index->right = NULL;
	//자식노드의 위치 지정
	if (parent != NULL) {
		if (compare(parent + 1, key) > 0) {
			parent->left = index;
		}
		else {
			parent->right = index;
		}
		//균형도 구하기
		if (compare(binaryTree->root + 1, key) > 0) {
			(binaryTree->balance)--;
		}
		else {
			(binaryTree->balance)++;
		}
	}
	else {
		binaryTree->root = index;
	}
	(binaryTree->length)++;
	return index;
}

BinaryNode* Search(BinaryTree* binaryTree, void* key, int(*compare)(void*, void*)) {
	BinaryNode* index;
	//루트노드 지정
	index = binaryTree->root;
	//키 값과 일치한 노드를 구한다
	while (index != NULL && compare(index + 1, key) != 0) {
		if (compare(index + 1, key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	return index;
}
/*
삭제시 고려해야 할 문제
1. 부모노드, 삭제노드, 삭제노드의 부모, 대체노드, 대체노드의 부모를 지정
2. 대체노드와 대체노드의 부모간의 관계
3. 삭제노드와 대체노드의 관계
4. 삭제노드의 부모와 대체노드간의 관계
5. 삭제노드가 말단에 위치할 시(대체노드가 없을 시)
6. 루트 키 값을 비교하여 균형도의 관계 설정
*/
BinaryNode* Delete(BinaryTree* binaryTree, void* key, int(*compare)(void*, void*)) {
	BinaryNode* index;
	BinaryNode* changeNode = NULL;
	BinaryNode* parentChangeNode = NULL;
	BinaryNode* deleteNode;
	BinaryNode* parentDeleteNode = NULL;

	deleteNode = binaryTree->root;
	while (deleteNode != NULL && compare(deleteNode + 1, key) != 0) {
		parentDeleteNode = deleteNode;
		if (compare(deleteNode + 1, key) > 0) {
			deleteNode = deleteNode->left;
		}
		else {
			deleteNode = deleteNode->right;
		}
	}
	index = deleteNode->right;
	while (index != NULL) {
		parentChangeNode = changeNode;
		changeNode = index;
		index = index->left;
	}
	if (deleteNode->right == NULL) {
		index = deleteNode->left;
	}
	while (index != NULL) {
		parentChangeNode = changeNode;
		changeNode = index;
		index = index->right;
	}
	if (changeNode != NULL && parentChangeNode == NULL) {
		parentChangeNode = deleteNode;
	}
	if (changeNode != NULL) {
		if (changeNode->left != NULL || changeNode->right != NULL) {
			if (parentChangeNode != deleteNode) {
				if (changeNode->left != NULL) {
					parentChangeNode->right = changeNode->left;
				}
				else {
					parentChangeNode->left = changeNode->right;
				}
			}
			else {
				if (changeNode->left != NULL) {
					parentChangeNode->left = changeNode->left;
				}
				else {
					parentChangeNode->right = changeNode->right;
				}
			}
		}
		else {
			if (parentChangeNode->left == changeNode) {
				parentChangeNode->left = NULL;
			}
			else {
				parentChangeNode->right = NULL;
			}
		}
		changeNode->left = deleteNode->left;
		changeNode->right = deleteNode->right;
		if (parentDeleteNode != NULL) {
			if (parentDeleteNode->left == deleteNode) {
				parentDeleteNode->left = changeNode;
			}
			else {
				parentDeleteNode->right = changeNode;
			}
		}
		else {
			binaryTree->root = changeNode;
		}
	}
	if(changeNode == NULL) {
		if (parentDeleteNode != NULL) {
			if (parentDeleteNode->left == deleteNode) {
				parentDeleteNode->left = NULL;
			}
			else {
				parentDeleteNode->right = NULL;
			}
		}
		else {
			binaryTree->root = NULL;
		}
	}
	if (deleteNode != NULL) {
		free(deleteNode);
	}
	binaryTree->length--;
	if (binaryTree->root != NULL) {
		if (parentDeleteNode != NULL) {
			if (compare(binaryTree->root + 1, key) > 0) {
				binaryTree->balance++;
			}
			else {
				binaryTree->balance--;
			}
		}
		else {
			if (compare(binaryTree->root + 1, key) < 0) {
				binaryTree->balance++;
			}
			else {
				binaryTree->balance--;
			}
		}
	}

	return NULL;
}

void MakeKeys(BinaryTree* binaryTree, void* (*keys), Long* count, size_t size) {
	Long i = 0;
	*count = 0;
	*keys = calloc(binaryTree->length, size);
	Node_MakeKeys(binaryTree->root, *keys, count, &i, size);
}

void Node_MakeKeys(BinaryNode* node, void(*keys), Long* count, Long *i, size_t size) {
	if (node != NULL) {
		Node_MakeKeys(node->left, keys, count, i, size);
		memcpy(((char(*))keys) + ((*i) * size), node + 1, size);
		(*i)++;
		(*count)++;
		Node_MakeKeys(node->right, keys, count, i, size);
	}
}

void DeleteAllItems(BinaryTree* binaryTree) {
	Node_DeleteAllItems(binaryTree->root);
	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

void Node_DeleteAllItems(BinaryNode* node) {
	if (node != NULL) {
		Node_DeleteAllItems(node->left);
		Node_DeleteAllItems(node->right);
		free(node);
	}
}

void MakeTree(BinaryTree* binaryTree, void(*keys), Long count, size_t size) {
	Long remainder;
	binaryTree->root = Node_MakeTree(keys, 0, count - 1, size);
	binaryTree->length = count;
	remainder = count % 2;
	if (remainder == 0) {
		binaryTree->balance = 1;
	}
	else {
		binaryTree->balance = 0;
	}
}

BinaryNode* Node_MakeTree(void(*keys), Long low, Long high, size_t size) {
	BinaryNode* node = NULL;
	Long middle;
	if (low <= high) {
		middle = (low + high) / 2;
		node = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
		memcpy(node + 1, ((char(*))keys) + (middle * size), size);
		node->left = Node_MakeTree(keys, low, middle - 1, size);
		node->right = Node_MakeTree(keys, middle + 1, high, size);
	}
	return node;
}

void MakeBalance(BinaryTree* binaryTree, size_t size) {
	void(*keys);
	Long count;
	MakeKeys(binaryTree, &keys, &count, size);
	DeleteAllItems(binaryTree);
	MakeTree(binaryTree, keys, count, size);
	if (keys != NULL) {
		free(keys);
	}
}

void GetAt(BinaryTree* binaryTree, BinaryNode* index, void* key, size_t size) {
	memcpy(key, index + 1, size);
}

void Destroy(BinaryTree* binaryTree) {
	Node_Destroy(binaryTree->root);
}

void Node_Destroy(BinaryNode* node) {
	if (node != NULL) {
		Node_Destroy(node->left);
		Node_Destroy(node->right);
		free(node);
	}
}