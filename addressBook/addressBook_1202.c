#include "adressBook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)


int main(int argc, char* arv[]) {
	Long index;
	Long indexes[MAX];
	Long count;
	Long i=0;
	AddressBook addressBook = { {{"","","",""}, {"","","",""}, {"","","",""}, {"","","",""}, {"","","",""}, {"","","",""}}, MAX, 0 };

	count = Load(&addressBook);
	printf("-------Record--------\n");
	index = Record(&addressBook, "최길동", "경기도", "031", "naver");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "윤길동", "대전시", "051", "daum");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "고길동", "대구시", "052", "gmail");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "정길동", "제주시", "012", "yahoo");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "윤길동", "고양시", "032", "empass");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);

	Find(&addressBook, "윤길동", indexes, &count);
	printf("-------Find--------\n");
	while (i < count) {
		printf("%d\t %s\t %s\t %s\t %s\n", indexes[i] + 1, addressBook.personals[indexes[i]].name, addressBook.personals[indexes[i]].address, addressBook.personals[indexes[i]].phoneNumber, addressBook.personals[indexes[i]].emailAddress);
		i++;
	}

	index = Correct(&addressBook, 1, "울산시", "123", "daum");
	printf("-------Correct--------\n");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);

	index = Erase(&addressBook, 4);
	printf("-------Erase--------\n");
	if (index == -1) {
		printf("지워졌습니다\n");
	}

	Arrange(&addressBook);

	i = 0;

	printf("-------Arrange--------\n");
	while (i < addressBook.length) {
		printf("%d\t %s\t %s\t %s\t %s\n", i + 1, addressBook.personals[i].name, addressBook.personals[i].address, addressBook.personals[i].phoneNumber, addressBook.personals[i].emailAddress);
		i++;
	}

	Save(&addressBook);

	return 0;
}


Long Load(AddressBook* addressBook) {
	Personal personal;
	Long i = 0;
	FILE* file = fopen("Personals.dat", "rb");
	if (file != NULL) {
		fread(&personal, sizeof(Personal), 1, file);
		while (!feof(file)) {
			addressBook->personals[i] = personal;
			i++;
			(addressBook->length)++;
			fread(&personal, sizeof(Personal), 1, file);
		}
		fclose(file);
	}
	return addressBook->length;
}

Long Record(AddressBook* addressBook, const char(*name), const char(*address), const char(*phoneNumber), const char(*emailAddress)) {
	Long i = 0;
	Long index = -1;
	while (i < addressBook->capacity && strcmp(addressBook->personals[i].name, "") != 0) {
		i++;
	}
	if (i < addressBook->capacity) {
		index = i;
		strcpy(addressBook->personals[index].name, name);
		strcpy(addressBook->personals[index].address, address);
		strcpy(addressBook->personals[index].phoneNumber, phoneNumber);
		strcpy(addressBook->personals[index].emailAddress, emailAddress);
		(addressBook->length)++;
	}
	return index;
}

void Find(AddressBook* addressBook, const char(*name), Long(*indexes), Long* count) {
	Long index = 0;
	Long i = 0;
	*count = 0;
	while (index < addressBook->length) {
		if (strcmp(addressBook->personals[index].name, name) == 0) {
			indexes[i] = index;
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
	strcpy(addressBook->personals[index].name, "X");
	index = -1;
	return index;
}

void Arrange(AddressBook* addressBook) {
	Personal temp;
	Long i = 0;
	Long j;
	Long k = 1;
	Long count = 0;
	while (i < addressBook->length) {
		j = 0;
		while (j < (addressBook->length) - i - 1) {
			if (strcmp(addressBook->personals[j].name, addressBook->personals[j + 1].name) < 0) {
				temp = addressBook->personals[j];
				addressBook->personals[j] = addressBook->personals[j + 1];
				addressBook->personals[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < addressBook->length && strcmp(addressBook->personals[i].name, "X") != 0) {
		count++;
		i++;
	}
	while (k < count) {
		temp = addressBook->personals[k];
		j = k - 1;
		while (j >= 0 && strcmp(addressBook->personals[j].name, temp.name) > 0) {
			addressBook->personals[j + 1] = addressBook->personals[j];
			j--;
		}
		addressBook->personals[j + 1] = temp;
		k++;
	}
}

Long Save(AddressBook* addressBook) {
	Long i = 0;
	FILE* file = fopen("Personals.dat", "wb");
	if (file != NULL) {
		while (i < addressBook->length) {
			fwrite(addressBook->personals + i, sizeof(Personal), 1, file);
			i++;
		}
		fclose(file);
	}
	return addressBook->length;
}
