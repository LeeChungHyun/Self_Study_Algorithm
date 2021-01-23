#include "AddressBook.h"
#include "Array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

int main(int argc, char* argv[]) {
	AddressBook addressBook;
	Long index;
	Long(*indexes);
	Long count;
	Long i;
	Personal personal;

	AddressBook_Create(&addressBook, 3);

	index = Record(&addressBook, "홍길동", "서울시", "01053216201", "hong@naver.com");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s\t%s\t%s\t%s\n", personal.name, personal.address, personal.phoneNumber, personal.emailAddress);

	index = Record(&addressBook, "고길동", "서울시", "01056216201", "ko@naver.com");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s\t%s\t%s\t%s\n", personal.name, personal.address, personal.phoneNumber, personal.emailAddress);

	index = Record(&addressBook, "고길동", "부산시", "05153216201", "ko@daum.com");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s\t%s\t%s\t%s\n", personal.name, personal.address, personal.phoneNumber, personal.emailAddress);

	index = Record(&addressBook, "박길동", "대구시", "03153216201", "park@naver.com");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s\t%s\t%s\t%s\n", personal.name, personal.address, personal.phoneNumber, personal.emailAddress);
	printf("\n");

	Find(&addressBook, "고길동", &indexes, &count);
	i = 0;
	while (i < count) {
		index = indexes[i];
		personal = AddressBook_GetAt(&addressBook, index);
		printf("%s\t%s\t%s\t%s\n", personal.name, personal.address, personal.phoneNumber, personal.emailAddress);
		i++;
	}
	printf("\n");
	if (indexes != NULL) {
		free(indexes);
	}

	index = Correct(&addressBook, 0, "제주시", "01033333333", "hong@naver.com");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s\t%s\t%s\t%s\n", personal.name, personal.address, personal.phoneNumber, personal.emailAddress);
	printf("\n");

	index = Erase(&addressBook, 3);
	if (index == -1) {
		printf("지워졌다!\n");
	}
	printf("\n");

	Arrange(&addressBook);
	i = 0;
	while (i < addressBook.length) {
		personal = AddressBook_GetAt(&addressBook, i);
		printf("%s\t%s\t%s\t%s\n", personal.name, personal.address, personal.phoneNumber, personal.emailAddress);
		i++;
	}
	printf("\n");

	AddressBook_Destroy(&addressBook);

	return 0;

}

void AddressBook_Create(AddressBook* addressBook, Long capacity) {
	Create(&addressBook->personals, capacity, sizeof(Personal));
	addressBook->capacity = capacity;
	addressBook->length = 0;
}

Long Record(AddressBook* addressBook, char(*name), char(*address), char(*phoneNumber), char(*emailAddress)) {
	Long index;
	Personal personal;

	strcpy(personal.name, name);
	strcpy(personal.address, address);
	strcpy(personal.phoneNumber, phoneNumber);
	strcpy(personal.emailAddress, emailAddress);
	if (addressBook->length < addressBook->capacity) {
		index = Store(&addressBook->personals, addressBook->length, &personal, sizeof(Personal));
	}
	else {
		index = AppendFromRear(&addressBook->personals, &personal, sizeof(Personal));
		addressBook->capacity++;
	}
	addressBook->length++;
	return index;
}

void Find(AddressBook* addressBook, char(*name), Long* (*indexes), Long* count) {
	LinearSearchDuplicate(&addressBook->personals, name, indexes, count, sizeof(Personal), CompareNames);
}

Long Correct(AddressBook* addressBook, Long index, char(*address), char(*phoneNumber), char(*emailAddress)) {
	Personal personal;

	GetAt(&addressBook->personals, index, &personal, sizeof(Personal));
	strcpy(personal.address, address);
	strcpy(personal.phoneNumber, phoneNumber);
	strcpy(personal.emailAddress, emailAddress);
	index = Modify(&addressBook->personals, index, &personal, sizeof(Personal));

	return index;
}

Long Erase(AddressBook* addressBook, Long index) {
	index = Delete(&addressBook->personals, index, sizeof(Personal));
	addressBook->capacity--;
	addressBook->length--;

	return index;
}

void Arrange(AddressBook* addressBook) {
	SelectionSort(&addressBook->personals, sizeof(Personal), ComparePersonals);
}

void AddressBook_Destroy(AddressBook* addressBook) {
	Destroy(&addressBook->personals);
}

Personal AddressBook_GetAt(AddressBook* addressBook, Long index) {
	Personal personal;
	GetAt(&addressBook->personals, index, &personal, sizeof(Personal));
	return personal;
}

int CompareNames(void* one, void* other) {
	Personal* one_ = (Personal*)one;
	char* other_ = (char*)other;
	return strcmp(one_->name, other_);
}

int ComparePersonals(void* one, void* other) {
	Personal* one_ = (Personal*)one;
	Personal* other_ = (Personal*)other;
	return strcmp(one_->name, other_->name);
}