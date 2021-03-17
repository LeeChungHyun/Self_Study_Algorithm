#include "BinaryTree.h"
#include <stdio.h>

int CompareKeys(void* one, void* other);
int main(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	BinaryTree binaryTree;
	BinaryNode* node;
	Long key;
	Long ret;
	//»ý¼º
	Create(&binaryTree);
#if 0
	key = 10;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d »ðÀÔ\n", ret);

	key = 40;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d »ðÀÔ\n", ret);

	key = 5;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d »ðÀÔ\n", ret);

	key = 79;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d »ðÀÔ\n", ret);

	key = 65;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d »ðÀÔ\n", ret);

	key = 120;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d »ðÀÔ\n", ret);

	key = 1045;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d »ðÀÔ\n", ret);

	key = 75;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d »ðÀÔ\n", ret);

	key = 90;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d »ðÀÔ\n", ret);

	key = 2;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d »ðÀÔ\n", ret);

	key = 120;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("»èÁ¦µÊ\n");
	}

	key = 10;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("»èÁ¦µÊ\n");
	}

	key = 40;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("»èÁ¦µÊ\n");
	}

	key = 75;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("»èÁ¦µÊ\n");
	}
	key = 90;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("»èÁ¦µÊ\n");
	}
	key = 2;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("»èÁ¦µÊ\n");
	}
	key = 79;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("»èÁ¦µÊ\n");
	}
	key = 1045;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("»èÁ¦µÊ\n");
	}
	key = 65;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("»èÁ¦µÊ\n");
	}
	key = 5;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("»èÁ¦µÊ\n");
	}
#endif
	//100»ðÀÔ
	key = 100;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d »ðÀÔ\n", ret);

	//50»ðÀÔ
	key = 50;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d »ðÀÔ\n", ret);

	//200»ðÀÔ
	key = 200;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d »ðÀÔ\n", ret);

	//300»ðÀÔ
	key = 300;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d »ðÀÔ\n", ret);

	//200Ã£±â
	key = 200;
	node = Search(&binaryTree, &key, CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d Ã£À½\n", ret);

	//150»ðÀÔ
	key = 150;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d »ðÀÔ\n", ret);

	//150»èÁ¦
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) { 
		printf("»èÁ¦µÊ\n"); 
	}

	//±ÕÇü ¸ÂÃß±â
	MakeBalance(&binaryTree, sizeof(Long));
	printf("±ÕÇü ¸ÂÃè½À´Ï´Ù\n");

	//¾ø¾Ö±â
	Destroy(&binaryTree);
	printf("Áö¿öÁ³½À´Ï´Ù\n");

	return 0;
}

int CompareKeys(void* one, void* other) {
	Long *one_  = (Long*)one;
	Long *other_ = (Long*)other;
	int ret;
	if (*one_ > *other_) { 
		ret = 1;
	}
	else if (*one_ == *other_) { 
		ret = 0;
	}
	else if (*one_ < *other_) { 
		ret = -1;
	}

	return ret;
}