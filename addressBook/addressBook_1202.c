#include "adressBook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

int main(int argc, char* arv[]) {
	Long index;
	Long indexes[MAX];
	Long count;
	Long i = 0;
	AddressBook addressBook = { {{"","","",""}, {"","","",""}, {"","","",""}, {"","","",""}, {"","","",""}, {"","","",""}}, MAX, 0 };


	printf("-------Record--------\n");
	index = Record(&addressBook, "�ֱ浿", "��⵵", "031", "naver");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "���浿", "������", "051", "daum");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "��浿", "�뱸��", "052", "gmail");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "���浿", "���ֽ�", "012", "yahoo");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);
	index = Record(&addressBook, "���浿", "����", "032", "empass");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);

	Find(&addressBook, "���浿", indexes, &count);
	printf("-------Find--------\n");
	while (i < count) {
		printf("%d\t %s\t %s\t %s\t %s\n", indexes[i] + 1, addressBook.personals[indexes[i]].name, addressBook.personals[indexes[i]].address, addressBook.personals[indexes[i]].phoneNumber, addressBook.personals[indexes[i]].emailAddress);
		i++;
	}

	index = Correct(&addressBook, 1, "����", "123", "daum");
	printf("-------Correct--------\n");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, addressBook.personals[index].name, addressBook.personals[index].address, addressBook.personals[index].phoneNumber, addressBook.personals[index].emailAddress);

	index = Erase(&addressBook, 4);
	printf("-------Erase--------\n");
	if (index == -1) {
		printf("���������ϴ�\n");
	}

	Arrange(&addressBook);

	i = 0;

	printf("-------Arrange--------\n");
	while (i < addressBook.length) {
		printf("%d\t %s\t %s\t %s\t %s\n", i + 1, addressBook.personals[i].name, addressBook.personals[i].address, addressBook.personals[i].phoneNumber, addressBook.personals[i].emailAddress);
		i++;
	}


	return 0;
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
