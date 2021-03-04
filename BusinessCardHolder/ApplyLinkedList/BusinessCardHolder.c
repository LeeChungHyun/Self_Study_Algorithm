#include "BusinessCardHolder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)

#if 0
int main(int argc, char* argv[]) {
	BusinessCardHolder businessCardHolder;
	BusinessCard businessCard;
	BusinessCard* index;
	BusinessCard* (*indexes);
	Long count;
	Long i;

	BusinessCard businessCard1 = { {"ȫ�浿", "011-321", "hong@naver.com","������"}, {"�Ｚ", "�����", "02-123", "02-456", "Samsung@re.kr"} };
	BusinessCard businessCard2 = { {"�ڱ浿", "010-5850", "park@naver.com","����"}, {"LG", "�����", "02-402", "021-406", "Lg@re.kr"} };
	BusinessCard businessCard3 = { {"���浿", "010-5321", "yoon@google.com","����"}, {"SKT", "������", "051-123", "051-456", "Skt@re.kr"} };
	BusinessCard businessCard4 = { {"���浿", "011-8321", "yoon@naver.com","�븮"}, {"KT", "����", "053-456", "053-789", "Kt@re.kr"} };

	//����
	BusinessCardHolder_Create(&businessCardHolder);
	printf("<����ø�� �����Ǿ����ϴ�>\n");

	//�ҷ�����
	Load(&businessCardHolder);

	//�ȱ�
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

	printf("<ù��° ���� ã��>\n");
	index = BusinessCardHolder_First(&businessCardHolder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain,
		index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position);

	printf("<���� ���� ã��>\n");
	index = BusinessCardHolder_Next(&businessCardHolder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain,
		index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position);

	printf("<������ ���� ã��>\n");
	index = BusinessCardHolder_Last(&businessCardHolder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain,
		index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position);

	printf("<���� ���� ã��>\n");
	index = BusinessCardHolder_Previous(&businessCardHolder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain,
		index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position);

	//�ش� ���� ����
	printf("<�ش� ���� ����>\n");
	businessCard = PutOut(&businessCardHolder, index);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", businessCard.company.name, businessCard.company.address, businessCard.company.phoneNumber, businessCard.company.fax, businessCard.company.domain,
		businessCard.personal.name, businessCard.personal.phoneNumber, businessCard.personal.emailAddress, businessCard.personal.position);

	//��ȣ�̸� ã��
	printf("<��ȣ�̸�ã��>\n");
	index = FindByCompanyName(&businessCardHolder, "�Ｚ");
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n\n", index->company.name, index->company.address, index->company.phoneNumber, index->company.fax, index->company.domain,
		index->personal.name, index->personal.phoneNumber, index->personal.emailAddress, index->personal.position);

	//����
	Save(&businessCardHolder);
	printf("����Ǿ���\n");

	//����
	BusinessCardHolder_Destroy(&businessCardHolder);
	printf("<���������ϴ�>\n");
	
	return 0;
}
#endif

void BusinessCardHolder_Create(BusinessCardHolder* businessCardHolder){
	Create(&businessCardHolder->businessCards);
	businessCardHolder->length = 0;
	businessCardHolder->current = NULL;
}

BusinessCard* PutIn(BusinessCardHolder* businessCardHolder, BusinessCard businessCard){
	Node* node;
	node = AppendFromTail(&businessCardHolder->businessCards, &businessCard, sizeof(BusinessCard));
	businessCardHolder->length++;
	businessCardHolder->current = (BusinessCard*)(node + 1);
	return businessCardHolder->current;
}

void Find(BusinessCardHolder* businessCardHolder, char(*name), BusinessCard** (*indexes), Long* count){
	Node* (*nodes);
	Long i;

	*indexes = (BusinessCard * (*))calloc(businessCardHolder->length, sizeof(BusinessCard*));
	LinearSearchDuplicate(&businessCardHolder->businessCards, name, &nodes, count, ComparePersonalNames);
	i = 0;
	while (i < *count){
		(*indexes)[i] = (BusinessCard*)(nodes[i] + 1);
		i++;
	}

	if (nodes != NULL){
		free(nodes);
	}
}

BusinessCard* FindByCompanyName(BusinessCardHolder* businessCardHolder, char(*companyName)){
	Node* node;
	BusinessCard* index = NULL;
	node = LinearSearchUnique(&businessCardHolder->businessCards, companyName, CompareCompanyNames);
	if (node != NULL){
		index = (BusinessCard*)(node + 1);
	}
	return index;
}

BusinessCard PutOut(BusinessCardHolder* businessCardHolder, BusinessCard* index){
	BusinessCard businessCard;
	Node* node;

	node = LinearSearchUnique(&businessCardHolder->businessCards, index, CompareBusinessCardLinks);
	GetAt(&businessCardHolder->businessCards, node, &businessCard, sizeof(BusinessCard));
	Delete(&businessCardHolder->businessCards, node);
	(businessCardHolder->length)--;

	if (businessCardHolder->businessCards.current != NULL){
		businessCardHolder->current = (BusinessCard*)(businessCardHolder->businessCards.current + 1);
	}
	return businessCard;
}

BusinessCard* BusinessCardHolder_First(BusinessCardHolder* businessCardHolder){
	Node* node;
	node = First(&businessCardHolder->businessCards);
	businessCardHolder->current = (BusinessCard*)(node + 1);
	return businessCardHolder->current;
}

BusinessCard* BusinessCardHolder_Previous(BusinessCardHolder* businessCardHolder){
	Node* node;
	node = Previous(&businessCardHolder->businessCards);
	businessCardHolder->current = (BusinessCard*)(node + 1);
	return businessCardHolder->current;
}

BusinessCard* BusinessCardHolder_Next(BusinessCardHolder* businessCardHolder){
	Node* node;
	node = Next(&businessCardHolder->businessCards);
	businessCardHolder->current = (BusinessCard*)(node + 1);
	return businessCardHolder->current;
}

BusinessCard* BusinessCardHolder_Last(BusinessCardHolder* businessCardHolder){
	Node* node;
	node = Last(&businessCardHolder->businessCards);
	businessCardHolder->current = (BusinessCard*)(node + 1);
	return businessCardHolder->current;
}

BusinessCard* BusinessCardHolder_Move(BusinessCardHolder* businessCardHolder, BusinessCard* index){
	Node* node;
	node = LinearSearchUnique(&businessCardHolder->businessCards, index, CompareBusinessCardLinks);
	node = Move(&businessCardHolder->businessCards, node);
	businessCardHolder->current = (BusinessCard*)(node + 1);
	return businessCardHolder->current;
}

Long Save(BusinessCardHolder* businessCardHolder) {
	BusinessCard businessCard;
	Node* node;
	Node* previous = NULL;
	Company company;
	Long count = 0;
	Long index;
	size_t flag;
	FILE* personalsFile = fopen("Personals.dat", "wb");
	FILE* companiesFile = fopen("Companies.dat", "wb+");

	if (personalsFile != NULL && companiesFile != NULL) {
		node = First(&businessCardHolder->businessCards);
		while (node != previous) {
			GetAt(&businessCardHolder->businessCards, node, &businessCard, sizeof(BusinessCard));
			index = 1;
			fseek(companiesFile, 0L, SEEK_SET);
			flag = fread(&company, sizeof(Company), 1, companiesFile);
			while (!feof(companiesFile) && flag != 0 && strcmp(businessCard.company.name, company.name) != 0) {
				index++;
				flag = fread(&company, sizeof(Company), 1, companiesFile);
			}
			if (flag == 0) {
				fwrite(&businessCard.company, sizeof(Company), 1, companiesFile);
			}
			fwrite(&index, sizeof(Long), 1, personalsFile);
			fwrite(&businessCard.personal, sizeof(Personal), 1, personalsFile);
			count++;
			previous = node;
			node = Next(&businessCardHolder->businessCards);
		}
		fclose(personalsFile);
		fclose(companiesFile);
	}
	return count;
}

Long Load(BusinessCardHolder* businessCardHolder) {
	BusinessCard businessCard;
	Company company;
	Personal personal;
	Node* node;
	Long index;
	Long i;
	size_t flag1;
	size_t flag2;
	FILE* personalsFile = fopen("Personals.dat", "rb");
	FILE* companinesFile = fopen("Companies.dat", "rb");

	if (personalsFile != NULL && companinesFile != NULL) {
		flag1 = fread(&index, sizeof(Long), 1, personalsFile);
		flag1 = fread(&personal, sizeof(Personal), 1, personalsFile);
		while (!feof(personalsFile) && flag1 != 0) {
			i = 1;
			fseek(companinesFile, 0L, SEEK_SET);
			flag2 = fread(&company, sizeof(Company), 1, companinesFile);
			while (!feof(companinesFile) && flag2 != 0 && i < index) {
				i++;
				flag2 = fread(&company, sizeof(Company), 1, companinesFile);
			}
			businessCard.personal = personal;
			businessCard.company = company;
			node = AppendFromTail(&businessCardHolder->businessCards, &businessCard, sizeof(BusinessCard));
			(businessCardHolder->length)++;
			businessCardHolder->current = (BusinessCard*)(node + 1);
			flag1 = fread(&index, sizeof(Long), 1, personalsFile);
			flag1 = fread(&personal, sizeof(Personal), 1, personalsFile);
		}
		fclose(personalsFile);
		fclose(companinesFile);
	}
	return businessCardHolder->length;
}

void BusinessCardHolder_Destroy(BusinessCardHolder* businessCardHolder){
	Destroy(&businessCardHolder->businessCards);
}

int ComparePersonalNames(void* one, void* other){
	BusinessCard* one_ = (BusinessCard*)one;
	char(*other_) = (char*)other;
	return strcmp(one_->personal.name, other);
}

int CompareCompanyNames(void* one, void* other){
	BusinessCard* one_ = (BusinessCard*)one;
	char(*other_) = (char*)other;
	return strcmp(one_->company.name, other_);
}

int CompareBusinessCardLinks(void* one, void* other){
	Node* one_ = one;
	BusinessCard* other_ = other;
	int ret;

	if ((BusinessCard*)one_ > other_){
		ret = 1;
	}
	else if ((BusinessCard*)one_ == other_){
		ret = 0;
	}
	else if ((BusinessCard*)one_ < other_){
		ret = -1;
	}
	return ret;
}