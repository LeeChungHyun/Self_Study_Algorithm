#ifndef _BINARYTREE_H
#define _BINARYTREE_H
#include <stddef.h>
typedef signed long int Long;
typedef struct _binaryNode BinaryNode;

typedef struct _binaryNode {
	BinaryNode* left;
	BinaryNode* right;
}BinaryNode;

typedef struct _binaryTree {
	BinaryNode* root;
	Long length;
	Long balance;
}BinaryTree;

void Create(BinaryTree* binaryTree);
BinaryNode* Insert(BinaryTree* binaryTree, void* key, size_t size, int(*compare)(void*, void*));
BinaryNode* Search(BinaryTree* binaryTree, void* key, int(*compare)(void*, void*));
BinaryNode* Delete(BinaryTree* binaryTree, void* key, int(*compare)(void*, void*));
void MakeKeys(BinaryTree* binaryTree, void* (*keys), Long* count, size_t size);
void Node_MakeKeys(BinaryNode* node, void(*keys), Long* count, Long* i, size_t size);
void DeleteAllItems(BinaryTree* binaryTree);
void Node_DeleteAllItems(BinaryNode* node);
void MakeTree(BinaryTree* binaryTree, void(*keys), Long count, size_t size);
BinaryNode* Node_MakeTree(void(*keys), Long low, Long high, size_t size);
void MakeBalance(BinaryTree* binaryTree, size_t size);
void Destroy(BinaryTree* binaryTree);
void Node_Destroy(BinaryNode* node);
void GetAt(BinaryTree* binaryTree, BinaryNode* index, void* key, size_t size);
#endif // !_BINARYTREE_H