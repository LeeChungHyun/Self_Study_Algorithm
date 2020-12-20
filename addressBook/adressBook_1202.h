//AddressBook.h
#ifndef _ADDRESSBOOK_H
#define _ADDRESSBOOK_H
#define MAX 6

typedef signed long int Long;
typedef struct _personal {
	char name[11];
	char address[64];
	char phoneNumber[12];
	char emailAddress[64];
}Personal;

typedef struct _addressBook {
	Personal personals[MAX];
	Long capacity;
	Long length;
}AddressBook;

Long Load(AddressBook* addressBook);
Long Record(AddressBook* addressBook, const char(*name), const char(*address), const char(*phoneNumber), const char(*emailAddress));
void Find(AddressBook* addressBook, const char(*name), Long(*indexes), Long* count);
Long Correct(AddressBook* addressBook, Long index, const char(*address), const char(*phoneNumber), const char(*emailAddress));
Long Erase(AddressBook* addressBook, Long index);
void Arrange(AddressBook* addressBook);
Long Save(AddressBook* addressBook);
#endif // !_ADDRESSBOOK_H
