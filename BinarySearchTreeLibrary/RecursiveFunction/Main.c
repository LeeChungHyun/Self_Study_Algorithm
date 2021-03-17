#include "BinaryTree.h"
#include <stdio.h>

int CompareKeys(void* one, void* other);
int main(int argc, char* argv[]);

int main(int argc, char* argv[]) {
	BinaryTree binaryTree;
	BinaryNode* node;
	Long key;
	Long ret;
	//����
	Create(&binaryTree);
#if 0
	key = 10;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d ����\n", ret);

	key = 40;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d ����\n", ret);

	key = 5;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d ����\n", ret);

	key = 79;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d ����\n", ret);

	key = 65;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d ����\n", ret);

	key = 120;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d ����\n", ret);

	key = 1045;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d ����\n", ret);

	key = 75;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d ����\n", ret);

	key = 90;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d ����\n", ret);

	key = 2;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d ����\n", ret);

	key = 120;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("������\n");
	}

	key = 10;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("������\n");
	}

	key = 40;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("������\n");
	}

	key = 75;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("������\n");
	}
	key = 90;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("������\n");
	}
	key = 2;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("������\n");
	}
	key = 79;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("������\n");
	}
	key = 1045;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("������\n");
	}
	key = 65;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("������\n");
	}
	key = 5;
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) {
		printf("������\n");
	}
#endif
	//100����
	key = 100;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d ����\n", ret);

	//50����
	key = 50;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d ����\n", ret);

	//200����
	key = 200;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d ����\n", ret);

	//300����
	key = 300;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d ����\n", ret);

	//200ã��
	key = 200;
	node = Search(&binaryTree, &key, CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d ã��\n", ret);

	//150����
	key = 150;
	node = Insert(&binaryTree, &key, sizeof(Long), CompareKeys);
	GetAt(&binaryTree, node, &ret, sizeof(Long));
	printf("%d ����\n", ret);

	//150����
	node = Delete(&binaryTree, &key, CompareKeys);
	if (node == NULL) { 
		printf("������\n"); 
	}

	//���� ���߱�
	MakeBalance(&binaryTree, sizeof(Long));
	printf("���� ������ϴ�\n");

	//���ֱ�
	Destroy(&binaryTree);
	printf("���������ϴ�\n");

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