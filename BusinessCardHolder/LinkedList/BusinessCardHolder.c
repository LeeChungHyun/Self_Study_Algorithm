#include "BusinessCardHolder.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

#if 0
int main(int argc, char* argv[]) {
	BusinessCardHolder businessCardHolder;
	BusinessCard businessCard1 = { {"ȫ�浿", "011-321", "hong@naver.com","������"}, {"�Ｚ", "�����", "02-123", "02-456", "Samsung@re.kr"}, NULL };
	BusinessCard businessCard2 = { {"�ڱ浿", "010-5850", "park@naver.com","����"}, {"LG", "�����", "02-402", "021-406", "Lg@re.kr"}, NULL };
	BusinessCard businessCard3 = { {"���浿", "010-5321", "yoon@google.com","����"}, {"SKT", "������", "051-123", "051-456", "Skt@re.kr"}, NULL };
	BusinessCard businessCard4 = { {"���浿", "011-8321", "yoon@naver.com","�븮"}, {"KT", "����", "053-456", "053-789", "Kt@re.kr"}, NULL };

	BusinessCard businessCard;
	BusinessCard *index;
	BusinessCard* (*indexes);
	BusinessCard* temp = NULL;
	Long count;
	Long i;

	Create(&businessCardHolder);
	printf("<�ȱ�>\n");
	index = PutIn(&businessCardHolder, businessCard1);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain,
		index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position);

	index = PutIn(&businessCardHolder, businessCard2);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain,
		index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position);

	index = PutIn(&businessCardHolder, businessCard3);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain,
		index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position);

	index = PutIn(&businessCardHolder, businessCard4);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain,
		index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position);
	
	
	printf("<ù��° ���� ã��>\n");
	index = First(&businessCardHolder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain,
		index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position);

	printf("<���� ���� ã��>\n");
	index = Next(&businessCardHolder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain,
		index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position);

	printf("<���� ���� ã��>\n");
	index = Previous(&businessCardHolder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain,
		index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position);

	printf("<���� �̵�>\n");
	index = Move(&businessCardHolder, index);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain,
		index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position);

	printf("<������ ���� ã��>\n");
	index = Last(&businessCardHolder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain,
		index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position);

	printf("<���� ������>\n");
	businessCard = PutOut(&businessCardHolder, index);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", businessCard.company.name, businessCard.company.address, businessCard.company.phoneNumber, businessCard.company.fax, businessCard.company.domain,
		businessCard.personal.name, businessCard.personal.phoneNumber, businessCard.personal.emailAddress, businessCard.personal.position);

	printf("<���� �ٽ� �ȱ�>\n");
	index = PutIn(&businessCardHolder, businessCard);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain,
		index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position);


	printf("<ã��>\n");
	Find(&businessCardHolder, "���浿", &indexes, &count);
	i = 0;
	while (i < count) {
		index = indexes[i];
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position,
			index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}
	printf("\n");

	printf("<�����ϱ�>\n");
	Arrange(&businessCardHolder);
	index = First(&businessCardHolder);
	while (index != temp) {
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position,
			index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain);
		temp = index;
		index = Next(&businessCardHolder);
	}

	//�����
	Destroy(&businessCardHolder);
	return 0;
}
#endif

void Create(BusinessCardHolder* businessCardHolder) {
	businessCardHolder->first = NULL;
	businessCardHolder->length = 0;
	businessCardHolder->current = NULL;
}

BusinessCard* PutIn(BusinessCardHolder* businessCardHolder, BusinessCard businessCard) {
	BusinessCard* previous = NULL;

	businessCardHolder->current = businessCardHolder->first;
	while (businessCardHolder->current != NULL) {
		previous = businessCardHolder->current;
		businessCardHolder->current = businessCardHolder->current->next;
	}
	businessCardHolder->current = (BusinessCard*)malloc(sizeof(BusinessCard));
	(*businessCardHolder->current) = businessCard;
	if (previous != NULL) {
		previous->next = businessCardHolder->current;
	}
	else {
		businessCardHolder->first = businessCardHolder->current;
	}
	(businessCardHolder->length)++;

	return businessCardHolder->current;
}

BusinessCard PutOut(BusinessCardHolder *businessCardHolder, BusinessCard* index) {
	BusinessCard *previous = NULL;
	BusinessCard businessCard;

	businessCardHolder->current = businessCardHolder->first;
	while (businessCardHolder->current != index) {
		previous = businessCardHolder->current;
		businessCardHolder->current = businessCardHolder->current->next;
	}
	if (previous != NULL) {
		previous->next = index->next;
	}
	else {
		businessCardHolder->first = index->next;
	}
	if (index->next != NULL) {
		businessCardHolder->current = index->next;
	}
	else {
		businessCardHolder->current = previous;
	}
	businessCard = *index;
	businessCard.next = NULL;
	if (index != NULL) {
		free(index);
	}
	(businessCardHolder->length)--;
	return businessCard;
}

void Find(BusinessCardHolder* businessCardHolder, char(*name), BusinessCard** (*indexes), Long* count) {
	Long i = 0;
	*count = 0;

	*indexes = (BusinessCard * (*))calloc(businessCardHolder->length, sizeof(BusinessCard*));
	businessCardHolder->current = businessCardHolder->first;
	while (businessCardHolder->current != NULL) {
		if (strcmp(businessCardHolder->current->personal.name, name) == 0) {
			(*indexes)[i] = businessCardHolder->current;
			i++;
			(*count)++;
		}
		businessCardHolder->current = businessCardHolder->current->next;
	}
}

BusinessCard* FindByCompanyName(BusinessCardHolder* businessCardHolder, char(*companyName)) {
	BusinessCard* index = NULL;
	businessCardHolder->current = businessCardHolder->first;
	while (businessCardHolder->current != NULL && strcmp(businessCardHolder->current->company.name, companyName) != 0) {
		businessCardHolder->current = businessCardHolder->current->next;
	}
	if (businessCardHolder != NULL) {
		index = businessCardHolder->current;
	}
	return index;
}

BusinessCard* First(BusinessCardHolder* businessCardHolder) {
	businessCardHolder->current = businessCardHolder->first;
	return businessCardHolder->current;
}

BusinessCard* Next(BusinessCardHolder* businessCardHolder) {
	BusinessCard* previous = businessCardHolder->current;
	businessCardHolder->current = businessCardHolder->current->next;
	if (businessCardHolder->current == NULL) {
		businessCardHolder->current = previous;
	}
	return businessCardHolder->current;
}

BusinessCard* Previous(BusinessCardHolder* businessCardHolder) {
	BusinessCard* previous = NULL;
	BusinessCard* current = businessCardHolder->current;

	businessCardHolder->current = businessCardHolder->first;
	while (businessCardHolder->current != current) {
		previous = businessCardHolder->current;
		businessCardHolder->current = businessCardHolder->current->next;
	}
	if (previous != NULL) {
		businessCardHolder->current = previous;
	}
	return businessCardHolder->current;
}

BusinessCard* Last(BusinessCardHolder* businessCardHolder) {
	BusinessCard* previous = NULL;
	while (businessCardHolder->current != NULL) {
		previous = businessCardHolder->current;
		businessCardHolder->current = businessCardHolder->current->next;
	}
	if (previous != NULL) {
		businessCardHolder->current = previous;
	}
	return businessCardHolder->current;
}

BusinessCard* Move(BusinessCardHolder* businessCardHolder, BusinessCard* index) {
	businessCardHolder->current = index;
	return businessCardHolder->current;
}

void Arrange(BusinessCardHolder* businessCardHolder) {
	BusinessCard* previous;
	BusinessCard* temp;
	BusinessCard* next;
	Long i = 1;
	Long j;
	while (i < businessCardHolder->length) {
		previous = NULL;
		businessCardHolder->current = businessCardHolder->first;
		next = businessCardHolder->current->next;
		j = 1;
		while (j <= businessCardHolder->length - i) {
			if (strcmp(businessCardHolder->current->personal.name, next->personal.name) > 0) {
				if (previous != NULL) {
					temp = previous->next;
					previous->next = businessCardHolder->current->next;
				}
				else {
					temp = businessCardHolder->first;
					businessCardHolder->first = businessCardHolder->current->next;
				}
				businessCardHolder->current->next = next->next;
				next->next = temp;
				previous = next;
			}
			else {
				previous = businessCardHolder->current;
				businessCardHolder->current = next;
			}
			next = businessCardHolder->current->next;
			j++;
		}
		i++;
	}
}

void Destroy(BusinessCardHolder* businessCardHolder) {
	businessCardHolder->current = businessCardHolder->first;
	while (businessCardHolder->current != NULL) {
		businessCardHolder->first = businessCardHolder->current->next;
		businessCardHolder->current = NULL;
		businessCardHolder->current = businessCardHolder->first;
	}
}

Long Load(BusinessCardHolder* businessCardHolder) {
	FILE* companiesFile = fopen("Companies.dat", "rb");
	FILE* personalsFile = fopen("Personals.dat", "rb");
	BusinessCard businessCard;
	Company company;
	Personal personal;
	BusinessCard* previous = NULL;
	Long i;
	Long index;
	Long flag1;
	Long flag2;

	if (personalsFile != NULL && companiesFile != NULL) {
		fread(&index, sizeof(Long), 1, personalsFile);
		flag1 = fread(&personal, sizeof(Personal), 1, personalsFile);
		while (!feof(personalsFile) && flag1 != 0) {
			i = 1;
			fseek(companiesFile, 0L, SEEK_SET);
			flag2 = fread(&company, sizeof(Company), 1, companiesFile);
			while (!feof(companiesFile) && flag2 != 0 && i < index) {
				i++;
				flag2 = fread(&company, sizeof(Company), 1, companiesFile);
			}
			businessCard.personal = personal;
			businessCard.company = company;
			businessCard.next = NULL;
			businessCardHolder->current = (BusinessCard*)malloc(sizeof(BusinessCard));
			*(businessCardHolder->current) = businessCard;
			if (previous != NULL) {
				previous->next = businessCardHolder->current;
			}
			else {
				businessCardHolder->first = businessCardHolder->current;
			}
			previous = businessCardHolder->current;
			(businessCardHolder->length)++;
			fread(&index, sizeof(Long), 1, personalsFile);
			flag1 = fread(&personal, sizeof(Personal), 1, personalsFile);
		}
		fclose(personalsFile);
		fclose(companiesFile);
	}
	return businessCardHolder->length;
}

Long Save(BusinessCardHolder* businessCardHolder) {
	Long count = 0;
	Company company;
	Long relationShip;
	FILE* personalsFile;
	FILE* companiesFile;
	Long flag;

	personalsFile = fopen("Personals.dat", "wb");
	companiesFile = fopen("Companies.dat", "wb+");

	if (personalsFile != NULL && companiesFile != NULL) {
		businessCardHolder->current = businessCardHolder->first;
		//1.���԰���ö�� ���� �ƴѵ��� �ݺ��Ѵ�.
		while (businessCardHolder->current != NULL) {
			relationShip = 1;
			fseek(companiesFile, 0L, SEEK_SET);
			flag = fread(&company, sizeof(Company), 1, companiesFile);
			//1.1. ������ ��ȣ�� ���� ��ȣ�� ȸ�����Ͽ��� ã�´�.
			while (!feof(companiesFile) && flag != 0 && strcmp(businessCardHolder->current->company.name, company.name) != 0) {
				relationShip++;
				flag = fread(&company, sizeof(Company), 1, companiesFile);
			}
			//1.2. ������ ȸ�����Ͽ� ȸ�縦 ����Ѵ�.
			if (flag == 0) {
				fwrite(&businessCardHolder->current->company, sizeof(Company), 1, companiesFile);
			}
			//1.3. ��ȣ�� ������ ����Ѵ�.
			fwrite(&relationShip, sizeof(Long), 1, personalsFile);
			fwrite(&businessCardHolder->current->personal, sizeof(Personal), 1, personalsFile);
			//1.4. ������ ������ ����.
			count++;
			businessCardHolder->current = businessCardHolder->current->next;
		}
		fclose(personalsFile);
		fclose(companiesFile);
	}
	//2. ������ ������ ����Ѵ�.
	return count;
	//3. ������.
}