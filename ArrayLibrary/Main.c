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

	//테스트 시나리오
	//1. 크기가 3인 배열을 만든다.
	Create(&array, 3, sizeof(Long));

	//2. 숫자10을 첫번째 위치에 저장한다.
	object = 10;
	index = Store(&array, 0, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//10

	//3. 숫자30을 두번째 위치에 저장한다.
	object = 30;
	index = Store(&array, 1, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//10 30

	//4. 숫자20을 세번째 위치에 저장한다.
	object = 20;
	index = Store(&array, 2, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//10 30 20

	//5. 숫자 5를 두번째 위치에 삽입한다.
	object = 5;
	index = Insert(&array, 1, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//10 5 30 20

	//6. 배열의 맨 앞에 숫자 40을 추가한다.
	object = 40;
	index = AppendFromFront(&array, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//40 10 5 30 20

	//7. 배열의 맨 뒤에 숫자 10을 추가한다.
	object = 10;
	index = AppendFromRear(&array, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//40 10 5 30 20 10

	//8. 숫자 20을 선형탐색한다.
	key = 20;
	index = LinearSearchUnique(&array, &key, sizeof(Long), CompareLongs);
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	//9.숫자 10을 선형탐색한다(복수선택).
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

	//10. 버블정렬하다.
	BubbleSort(&array, sizeof(Long), CompareLongs);
	i = 0;
	while (i < array.length) {
		GetAt(&array, i, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}
	printf("\n");											//5 10 10 20 30 40

	//11. 두번째 위치를 지운다.
	index = Delete(&array, 1, sizeof(Long));
	if (index == -1) {
		printf("지워졌습니다\n");
	}														//5 10 20 30 40

	//12. 배열의 맨 뒷값을 지운다.
	index = DeleteFromRear(&array, sizeof(Long));
	if (index == -1) {
		printf("지워졌습니다\n");
	}														//5 10 20 30

	//13. 배열의 맨 앞값을 지운다.
	index = DeleteFromFront(&array, sizeof(Long));
	if (index == -1) {
		printf("지워졌습니다\n");
	}														//10 20 30

	//14. 두번째 위치에 숫자15으로 변경한다.
	object = 15;
	index = Modify(&array, 1, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//10 15 30

	//15. 배열을 지운다.
	Clear(&array);
	if (array.front == NULL) {
		printf("클리어했습니다\n");
	}

	//16.크기가 2인 one 배열을 생성한다.
	Create(&one, 2, sizeof(Long));

	//17. 숫자50을 one의 첫번째 위치에 저장한다.
	object = 50;
	index = Store(&one, 0, &object, sizeof(Long));
	GetAt(&one, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//50

	//18. 숫자30을 one의 두번째 위치에 저장한다.
	object = 30;
	index = Store(&one, 1, &object, sizeof(Long));
	GetAt(&one, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//50 30

	//19. one 배열을 선택정렬한다.
	SelectionSort(&one, sizeof(Long), CompareLongs);
	i = 0;
	while (i < one.length) {
		GetAt(&one, i, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}
	printf("\n");											//30 50

	//20. 크기가 2인 other 배열을 생성한다.
	Create(&other, 2, sizeof(Long));

	//21. 숫자40을 other의 첫번째 위치에 저장한다.
	object = 40;
	index = Store(&other, 0, &object, sizeof(Long));
	GetAt(&other, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//40

	//22. 숫자10을 other의 첫번째 위치에 저장한다.
	object = 10;
	index = Store(&other, 1, &object, sizeof(Long));
	GetAt(&other, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//40 10

	//23. 삽입정렬한다.
	InsertionSort(&other, sizeof(Long), CompareLongs);
	i = 0;
	while (i < other.length) {
		GetAt(&other, i, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}
	printf("\n");											//10 40

	//24. 병합정렬한다.
	MergeSort(&array, one, other, sizeof(Long), CompareLongs);
	i = 0;
	while (i < array.length) {
		GetAt(&array, i, &ret, sizeof(Long));
		printf("%d ", ret);
		i++;
	}
	printf("\n");											//10 30 40 50

	//25. 40을 이분검색한다.
	key = 40;
	index = BinerySearchUnique(&array, &key, sizeof(Long), CompareLongs);
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	//26. 배열 맨 뒤에 50을 추가한다.
	object = 50;
	index = AppendFromRear(&array, &object, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);									//10 30 40 50 50

	//27. 숫자 50을 이분검색한다(복수탐색)
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

	//28. array배열을 없앤다.
	Destroy(&array);

	//29. one배열을 없앤다.
	Destroy(&one);

	//30. other배열을 없앤다.
	Destroy(&other);

	return 0;
}

//매개변수 크기비교 함수
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