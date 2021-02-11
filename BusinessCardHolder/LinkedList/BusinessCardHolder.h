#ifndef _BUSINESSCARDHOLDER_H
#define _BUSINESSCARDHOLDER_H

typedef signed long int Long;
typedef struct _personal {
	char name[11];
	char phoneNumber[12];
	char emailAddress[64];
	char position[16];
}Personal;

typedef struct _company {
	char name[64];
	char address[64];
	char phoneNumber[12];
	char fax[12];
	char domain[64];
}Company;

typedef struct _businessCard BusinessCard;

typedef struct _businessCard {
	Personal personal;
	Company company;
	BusinessCard* next;
}BusinessCard;

typedef struct _businessCardHolder {
	BusinessCard* first;
	Long length;
	BusinessCard* current;
}BusinessCardHolder;

void Create(BusinessCardHolder* businessCardHolder);
BusinessCard* PutIn(BusinessCardHolder* businessCardHolder, BusinessCard businessCard);
void Find(BusinessCardHolder* businessCardHolder, char(*name), BusinessCard** (*indexes), Long* count);
BusinessCard* FindByCompanyName(BusinessCardHolder* businessCardHolder, char(*companyName));
BusinessCard PutOut(BusinessCardHolder* businessCardHolder, BusinessCard* index);
void Arrange(BusinessCardHolder* businessCardHolder);
BusinessCard* First(BusinessCardHolder* businessCardHolder);
BusinessCard* Next(BusinessCardHolder* businessCardHolder);
BusinessCard* Previous(BusinessCardHolder* businessCardHolder);
BusinessCard* Last(BusinessCardHolder* businessCardHolder);
BusinessCard* Move(BusinessCardHolder* businessCardHolder, BusinessCard* index);
void Destroy(BusinessCardHolder* businessCardHolder);
Long Load(BusinessCardHolder* businessCardHolder);
Long Save(BusinessCardHolder* businessCardHolder);
#endif // !_BUSINESSCARDHOLDER_H