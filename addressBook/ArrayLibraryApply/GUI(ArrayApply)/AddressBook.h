#ifndef _ADDRESSBOOK_H
#define _ADDRESSBOOK_H
#include "Array.h"

typedef signed long int Long;
typedef struct _personal {
	char name[11];
	char address[64];
	char phoneNumber[12];
	char emailAddress[64];
}Personal;
typedef struct _addressBook {
	Array personals;
	Long capacity;
	Long length;
}AddressBook;

Long Load(AddressBook* addressBook);
void AddressBook_Create(AddressBook* addressBook, Long capacity);
Long Record(AddressBook* addressBook, char(*name), char(*address), char(*phoneNumber), char(*emailAddress));
void Find(AddressBook* addressBook, char(*name), Long* (*indexes), Long* count);
Long Correct(AddressBook* addressBook, Long index, char(*address), char(*phoneNumber), char(*emailAddress));
Long Erase(AddressBook* addressBook, Long index);
void Arrange(AddressBook* addressBook);
void AddressBook_Destroy(AddressBook* addressBook);
Personal AddressBook_GetAt(AddressBook* addressBook, Long index);
Long Save(AddressBook* addressBook);
int CompareNames(void* one, void* other);
int ComparePersonals(void* one, void* other);
#endif //_ADDRESSBOOK_H