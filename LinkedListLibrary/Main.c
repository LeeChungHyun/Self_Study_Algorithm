#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

int Compare(void* one, void* other);

int main(int argc, char* argv[]) {
	LinkedList linkedList;
	Long object;
	Long ret;
	Long key;
	Long count;
	Long i;
	Node* index;
	Node* (*indexes);

	
	//1. ���Ḯ��Ʈ ����
	Create(&linkedList);
	//2. �� �� ��� �߰�
	object = 100;
	index = AppendFromTail(&linkedList, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//3. �� �� ��� �߰�
	object = 50;
	index = AppendFromHead(&linkedList, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//4. ��� 150 ����
	object = 150;
	index = InsertAfter(&linkedList, index, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//5. ó�� ���
	index = First(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//6. ��� 10 ����
	object = 10;
	index = InsertBefore(&linkedList, index, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//7. ������ ���
	index = Last(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	//8. ���� ���
	index = Previous(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	//9. �ǳ� �����
	index = DeleteFromTail(&linkedList);
	if (index == NULL) { 
		printf("�ǳ� ��� ��������\n");
	}
	
	//10. ��� 50 ã��
	key = 50;
	index = LinearSearchUnique(&linkedList, &key, Compare);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	
	//11. ���� ���
	index = Next(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	//12. 150 ����
	index = Delete(&linkedList, index);
	if (index == NULL) { printf("���� ��� ��������\n"); }

	//13. ��  50 �߰�
	object = 50;
	index = AppendFromTail(&linkedList, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	//14. ��� 50 ã��(����)
	key = 50;
	LinearSearchDuplicate(&linkedList, &key, &indexes, &count, Compare);
	i = 0;
	while (i < count) {
		index = indexes[i];
		GetAt(&linkedList, index, &object, sizeof(Long));
		printf("%d", object);
		i++;
	}
	printf("\n");

	//15. ��� 10���� �̵��Ѵ�.
	index = indexes[0];
	index = Move(&linkedList, index);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	//16. �� �� ��� ����
	index = DeleteFromHead(&linkedList);
	if (index == NULL) {
		printf("�� �� ��� ����\n");
	}

	//17.��ü ��� �����.
	DeleteAllItems(&linkedList);
	if (linkedList.length == 0) {
		printf("��ü ��� ����\n");
	}

	//18. ���Ḯ��Ʈ�� �����.
	Destroy(&linkedList);
	return 0;
}

int Compare(void* one, void* other) {
	Long* one_ = (Long*)one;
	Long* other_ = (Long*)other;
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