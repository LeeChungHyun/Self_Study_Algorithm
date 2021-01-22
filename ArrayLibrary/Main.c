#include "Array.h"
#include <stdio.h>
#include <stdlib.h>
int CompareLongs(void* one, void* other);

int main(int argc, char* argv[]) {
	Array array;
	Array one;
	Array other;
	Long object;
	Long key;
	Long index;
	Long(*indexes);
	Long count;
	Long ret;
	Long i;

	//�׽�Ʈ �ó�����
	//1. ũ�Ⱑ 3�� �迭�� �����.
	Create(&array, 3, sizeof(Long));

	//2. ����10�� ù��° ��ġ�� �����Ѵ�.
	object = 10;
	index = Store(&array, 0, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//10

	//3. ����30�� �ι�° ��ġ�� �����Ѵ�.
	object = 30;
	index = Store(&array, 1, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//10 30

	//4. ����20�� ����° ��ġ�� �����Ѵ�.
	object = 20;
	index = Store(&array, 2, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//10 30 20

	//5. ���� 5�� �ι�° ��ġ�� �����Ѵ�.
	object = 5;
	index = Insert(&array, 1, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//10 5 30 20

	//6. �迭�� �� �տ� ���� 40�� �߰��Ѵ�.
	object = 40;
	index = AppendFromFront(&array, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//40 10 5 30 20

	//7. �迭�� �� �ڿ� ���� 10�� �߰��Ѵ�.
	object = 10;
	index = AppendFromRear(&array, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//40 10 5 30 20 10

	//8. ���� 20�� ����Ž���Ѵ�.
	key = 20;
	index = LinearSearchUnique(&array, &key, sizeof(Long), CompareLongs);
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	//9.���� 10�� ����Ž���Ѵ�(��������).
	key = 10;
	LinearSearchDuplicate(&array, &key, &indexes, &count, sizeof(Long), CompareLongs);
	i = 0;
	while (i < count) {
		index = indexes[i];
		GetAt(&array, index, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}
	printf("\n");
	if (indexes != NULL) {
		free(indexes);
	}

	//10. ���������ϴ�.
	BubbleSort(&array, sizeof(Long), CompareLongs);
	i = 0;
	while (i < array.length) {
		GetAt(&array, i, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}
	printf("\n");											//5 10 10 20 30 40

	//11. �ι�° ��ġ�� �����.
	index = Delete(&array, 1, sizeof(Long));
	if (index == -1) {
		printf("���������ϴ�\n");
	}														//5 10 20 30 40

	//12. �迭�� �� �ް��� �����.
	index = DeleteFromRear(&array, sizeof(Long));
	if (index == -1) {
		printf("���������ϴ�\n");
	}														//5 10 20 30

	//13. �迭�� �� �հ��� �����.
	index = DeleteFromFront(&array, sizeof(Long));
	if (index == -1) {
		printf("���������ϴ�\n");
	}														//10 20 30

	//14. �ι�° ��ġ�� ����15���� �����Ѵ�.
	object = 15;
	index = Modify(&array, 1, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//10 15 30

	//15. �迭�� �����.
	Clear(&array);
	if (array.front == NULL) {
		printf("Ŭ�����߽��ϴ�\n");
	}

	//16.ũ�Ⱑ 2�� one �迭�� �����Ѵ�.
	Create(&one, 2, sizeof(Long));

	//17. ����50�� one�� ù��° ��ġ�� �����Ѵ�.
	object = 50;
	index = Store(&one, 0, &object, sizeof(Long));
	GetAt(&one, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//50

	//18. ����30�� one�� �ι�° ��ġ�� �����Ѵ�.
	object = 30;
	index = Store(&one, 1, &object, sizeof(Long));
	GetAt(&one, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//50 30

	//19. one �迭�� ���������Ѵ�.
	SelectionSort(&one, sizeof(Long), CompareLongs);
	i = 0;
	while (i < one.length) {
		GetAt(&one, i, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}
	printf("\n");											//30 50

	//20. ũ�Ⱑ 2�� other �迭�� �����Ѵ�.
	Create(&other, 2, sizeof(Long));

	//21. ����40�� other�� ù��° ��ġ�� �����Ѵ�.
	object = 40;
	index = Store(&other, 0, &object, sizeof(Long));
	GetAt(&other, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//40

	//22. ����10�� other�� ù��° ��ġ�� �����Ѵ�.
	object = 10;
	index = Store(&other, 1, &object, sizeof(Long));
	GetAt(&other, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//40 10

	//23. ���������Ѵ�.
	InsertionSort(&other, sizeof(Long), CompareLongs);
	i = 0;
	while (i < other.length) {
		GetAt(&other, i, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}
	printf("\n");											//10 40

	//24. ���������Ѵ�.
	MergeSort(&array, one, other, sizeof(Long), CompareLongs);
	i = 0;
	while (i < array.length) {
		GetAt(&array, i, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}
	printf("\n");											//10 30 40 50

	//25. 40�� �̺а˻��Ѵ�.
	key = 40;
	index = BinerySearchUnique(&array, &key, sizeof(Long), CompareLongs);
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	//26. �迭 �� �ڿ� 50�� �߰��Ѵ�.
	object = 50;
	index = AppendFromRear(&array, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//10 30 40 50 50

	//27. ���� 50�� �̺а˻��Ѵ�(����Ž��)
	key = 50;
	BinerySearchDuplicate(&array, &key, &indexes, &count, sizeof(Long), CompareLongs);
	i = 0;
	while (i < count) {
		index = indexes[i];
		GetAt(&array, index, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}
	printf("\n");
	if (indexes != NULL) {
		free(indexes);
	}

	//28. array�迭�� ���ش�.
	Destroy(&array);

	//29. one�迭�� ���ش�.
	Destroy(&one);

	//30. other�迭�� ���ش�.
	Destroy(&other);

	return 0;
}

//�Ű����� ũ��� �Լ�
int CompareLongs(void* one, void* other) {
	Long* one_ = (Long*)one;
	Long* other_ = (Long*)other;
	int ret;
	if (*one_ > *other_) {
		ret = 1;
	}
	else if (*one_ == *other_) {
		ret = 0;
	}
	if (*one_ < *other_) {
		ret = -1;
	}
	return ret;
}