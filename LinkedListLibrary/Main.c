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

	
	//1. 연결리스트 생성
	Create(&linkedList);
	
	//2. 맨 뒤 노드 추가
	object = 100;
	index = AppendFromTail(&linkedList, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	
	//3. 맨 앞 노드 추가
	object = 50;
	index = AppendFromHead(&linkedList, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	
	//4. 노드 150 삽입
	object = 150;
	index = InsertAfter(&linkedList, index, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	
	//5. 처음 노드
	index = First(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	
	//6. 노드 10 삽입
	object = 10;
	index = InsertBefore(&linkedList, index, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	
	//7. 마지막 노드
	index = Last(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	
	//8. 이전 노드
	index = Previous(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	//9. 맨끝 지우기
	index = DeleteFromTail(&linkedList);
	if (index == NULL) { 
		printf("맨끝 노드 지워봉\n");
	}
	
	//10. 노드 50 찾기
	key = 50;
	index = LinearSearchUnique(&linkedList, &key, Compare);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	
	//11. 다음 노드
	index = Next(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	//12. 150 삭제
	index = Delete(&linkedList, index);
	if (index == NULL) { printf("현재 노드 지워봉\n"); }

	//13. 맨  50 추가
	object = 50;
	index = AppendFromTail(&linkedList, &object, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	//14. 노드 50 찾기(복수)
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

	//15. 노드 10으로 이동한다.
	index = indexes[0];
	index = Move(&linkedList, index);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	//16. 맨 앞 노드 삭제
	index = DeleteFromHead(&linkedList);
	if (index == NULL) {
		printf("맨 앞 노드 삭제\n");
	}

	//17.전체 노드 지운다.
	DeleteAllItems(&linkedList);
	if (linkedList.length == 0) {
		printf("전체 노드 삭제\n");
	}

	//18. 연결리스트를 지운다.
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
