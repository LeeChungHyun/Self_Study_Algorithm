//12.20
#ifndef _ADDRESSBOOK_HEAP
#define _ADDRESSBOOK_HEAP
typedef signed long int Long;
typedef struct _personal {
	char name[11];
	char address[64];
	char phoneNumber[12];
	char emailAddress[64];
}Personal;

typedef struct _addressBook {
	Personal (*personals);
	Long capacity;
	Long length;
}AddressBook;

void Create(AddressBook* addressBook, Long capacity);
Long Record(AddressBook* addressBook, const char(*name), const char(*address), const char(*phoneNumber), const char(*emailAddress));
void Find(AddressBook* addressBook, const char(*name), Long* (*indexes), Long* count);
Long Correct(AddressBook* addressBook, Long index, const char(*address), const char(*phoneNumber), const char(*emailAddress));
Long Erase(AddressBook* addressBook, Long index);
void Arrange(AddressBook* addressBook);
void Destroy(AddressBook* addressBook);
#endif // !_ADDRESSBOOK_HEAP

