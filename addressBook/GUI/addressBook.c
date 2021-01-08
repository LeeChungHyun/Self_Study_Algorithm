#include "addressBook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

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