#include "addressBook_Heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

/*
int main(int argc, char* argv[]) {
	AddressBook addressBook;
	Long index;
	Long (*indexes);
	Long count;
	Long i = 0;

	Create(&addressBook, 2);
	count = Load(&addressBook);
#if 0
	printf("-----------Record-----------\n");
	index = Record(&addressBook, "최길동", "경기도", "031", "naver");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "윤길동", "대전시", "051", "daum");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "홍길동", "서울시", "010", "gmail");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "고길동", "대전시", "012", "empass");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "홍길동", "대구시", "013", "google");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);


	printf("------------Find------------\n");
	Find(&addressBook, "홍길동", &indexes, &count);
	while (i < count) {
		printf("%d\t %s\t %s\t %s\t %s\n", indexes[i] + 1, addressBook.personals[indexes[i]].name, addressBook.personals[indexes[i]].address, addressBook.personals[indexes[i]].phoneNumber, addressBook.personals[indexes[i]].emailAddress);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}

	printf("-----------Correct----------\n");
	index = Correct(&addressBook, 1, "울산시", "123", "daum");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);
	
	printf("------------Erase-----------\n");
	index = Erase(&addressBook, 3);
	if (index == -1) {
		printf("지워졌습니다\n");
	}

	printf("-----------Arrange----------\n");
	Arrange(&addressBook);
	i = 0;
	while (i < addressBook.length) {
		printf("%d\t %s\t %s\t %s\t %s\n", i + 1 , addressBook.personals[i].name, addressBook.personals[i].address, addressBook.personals[i].phoneNumber, addressBook.personals[i].emailAddress);
		i++;
	}
	Save(&addressBook);
#endif
	while (i < count) {
		printf("%d\t %s\t %s\t %s\t %s\n", i + 1, addressBook.personals[i].name, addressBook.personals[i].address, addressBook.personals[i].phoneNumber, addressBook.personals[i].emailAddress);
		i++;
	}
	
	
	
	Destroy(&addressBook);
	return 0;
}
*/

void Create(AddressBook* addressBook, Long capacity) {
	addressBook->personals = (Personal(*))calloc(capacity, sizeof(Personal));
	addressBook->capacity = capacity;
	addressBook->length = 0;
}

Long Load(AddressBook* addressBook) {
	Personal(*temp);
	Personal personal;
	FILE* file;
	Long i;
	Long j = 0;
	file = fopen("AddressBook.dat", "rb");
	if (file != NULL) {
		fread(&personal, sizeof(Personal), 1, file);
		while (!feof(file)) {
			if (addressBook->length >= addressBook->capacity) {
				temp = (Personal(*))calloc((addressBook->capacity) + 1, sizeof(Personal));
				i = 0;
				while (i < addressBook->length) {
					temp[i] = addressBook->personals[i];
					i++;
				}
				if (addressBook->personals != NULL) {
					free(addressBook->personals);
				}
				addressBook->personals = temp;
				(addressBook->capacity)++;
			}
			addressBook->personals[j] = personal;
			j++;
			(addressBook->length)++;
			fread(&personal, sizeof(Personal), 1, file);
		}
		fclose(file);
	}
	return addressBook->length;
}


Long Record(AddressBook* addressBook, const char(*name), const char(*address), const char(*phoneNumber), const char(*emailAddress)) {
	Personal(*temp);
	Long index;
	Long i = 0;
	
	if (addressBook->length >= addressBook->capacity) {
		temp = (Personal(*))calloc((addressBook->capacity)+1, sizeof(Personal));
		while (i < addressBook->length) {
			temp[i] = addressBook->personals[i];
			i++;
		}

		if (addressBook->personals != NULL) {
			free(addressBook->personals);
		}

		addressBook->personals = temp;
		(addressBook->capacity)++;
	}
	index = addressBook->length;
	strcpy(addressBook->personals[index].name, name);
	strcpy(addressBook->personals[index].address, address);
	strcpy(addressBook->personals[index].phoneNumber, phoneNumber);
	strcpy(addressBook->personals[index].emailAddress, emailAddress);
	(addressBook->length)++;
	return index;
}

void Find(AddressBook* addressBook, const char(*name), Long* (*indexes), Long* count) {
	Long index = 0;
	Long i = 0;
	*count = 0;
	*indexes = (Long(*))calloc(addressBook->length, sizeof(Long));

	while (index < addressBook->length) {
		if (strcmp(addressBook->personals[index].name, name) == 0) {
			(*indexes)[i] = index;
			i++;
			(*count)++;
		}
		index++;
	}
}

Long Correct(AddressBook* addressBook, Long index, const char(*address), const char(*phoneNumber), const char(*emailAddress)) {
	strcpy(addressBook->personals[index].address, address);
	strcpy(addressBook->personals[index].phoneNumber, phoneNumber);
	strcpy(addressBook->personals[index].emailAddress, emailAddress);
	return index;
}

Long Erase(AddressBook* addressBook, Long index) {
	Personal (*temp)= NULL;
	Long i = 0;
	Long j = 0;

	if (addressBook->capacity > 1) {
		temp = (Personal(*))calloc((addressBook->capacity) - 1, sizeof(Personal));
	}
	while (i < index) {
		temp[j] = addressBook->personals[i];
		j++;
		i++;
	}
	i = index + 1;

	while (i < addressBook->length) {
		temp[j] = addressBook->personals[i];
		j++;
		i++;
	}
	if (addressBook->personals != NULL) {
		free(addressBook->personals);
		addressBook->personals = NULL;
	}
	if (addressBook->capacity > 1) {
		addressBook->personals = temp;
	}
	(addressBook->length)--;
	(addressBook->capacity)--;
	index = -1;
	return index;
}

void Arrange(AddressBook* addressBook) {
	Personal temp;
	Long i = 0;
	Long j;
	while (i < addressBook->length) {
		j = 0;
		while (j < (addressBook->length) - i - 1) {
			if (strcmp(addressBook->personals[j].name, addressBook->personals[j + 1].name) > 0) {
				temp = addressBook->personals[j];
				addressBook->personals[j] = addressBook->personals[j + 1];
				addressBook->personals[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void Destroy(AddressBook* addressBook) {
	if (addressBook->personals != NULL) {
		free(addressBook->personals);
	}
}

Long Save(AddressBook* addressBook) {
	Long i = 0;
	FILE* file;
	file = fopen("AddressBook.dat", "wb");
	if (file != NULL) {
		while (i < addressBook->length) {
			fwrite(addressBook->personals + i, sizeof(Personal), 1, file);
			i++;
		}
		fclose(file);
	}
	return addressBook->length;
}
