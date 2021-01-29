#include "AddressBook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

Long Load(AddressBook* addressBook) {
	Personal personal;
	size_t flag;

	FILE* file = fopen("AddressBook.dat", "rb");
	if (file != NULL) {
		flag = fread(&personal, sizeof(Personal), 1, file);
		while (!feof(file) && flag != 0) {
			if (addressBook->length < addressBook->capacity) {
				Store(&addressBook->personals, addressBook->length, &personal, sizeof(Personal));
			}
			else {
				AppendFromRear(&addressBook->personals, &personal, sizeof(Personal));
				addressBook->capacity++;
			}
			addressBook->length++;
			flag = fread(&personal, sizeof(Personal), 1, file);
		}
		fclose(file);
	}
	return addressBook->length;
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

Long Save(AddressBook* addressBook) {
	Personal personal;
	Long i;

	FILE* file = fopen("AddressBook.dat", "wb");
	if (file != NULL) {
		i = 0;
		while (i < addressBook->length) {
			GetAt(&addressBook->personals, i, &personal, sizeof(Personal));
			fwrite(&personal, sizeof(Personal), 1, file);
			i++;
		}
		fclose(file);
	}

	return addressBook->length;
}

int CompareNames(void* one, void* other) {
	Personal* one_ = (Personal*)one;
	char(*other_) = (char(*))other;

	return strcmp(one_->name, other_);
}
int ComparePersonals(void* one, void* other) {
	Personal* one_ = (Personal*)one;
	Personal* other_ = (Personal*)other;

	return strcmp(one_->name, other_->name);
}