//form.c
#include "form.h"
#include "addressBook_Heap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

int main(int argc, char* argv[]) {
	AddressBook addressBook;
	int menu;
	Create(&addressBook, 2);
	DisplayMenu();
	rewind(stdin); scanf("%d", &menu);
	while (menu != 0) {
		switch(menu){
			case 1: FormForRecording(&addressBook); break;
			case 2 : FormForFinding(&addressBook); break;
			case 3: FormForCorrecting(&addressBook); break;
			case 4: FormForErasing(&addressBook); break;
			case 5: FormForArranging(&addressBook); break;
			case 6: FormForShowAll(&addressBook); break;
			default:
				break;
		}
		DisplayMenu();
		rewind(stdin); scanf("%d", &menu);
	}
	Destroy(&addressBook);
	return 0;
}

void DisplayMenu() {
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t     �ּҷ� Version 0.05\n");
	printf("\t\t\t     =========================================\n");
	printf("\t\t\t     [1] �����ϱ�\n");
	printf("\t\t\t     [2] ã    ��\n");
	printf("\t\t\t     [3] �� ġ ��\n");
	printf("\t\t\t     [4] �� �� ��\n");
	printf("\t\t\t     [5] �����ϱ�\n");
	printf("\t\t\t     [6] ��ü����\n");
	printf("\t\t\t     [0] �� �� ��\n");
	printf("\t\t\t     -----------------------------------------\n");
	printf("\t\t\t     �޴��� �����Ͻʽÿ�! ");
}

void FormForRecording(AddressBook* addressBook) {
	char name[11];
	char address[64];
	char phoneNumber[12];
	char emailAddress[64];
	char recording;
	char going = 'Y';
	Long index;
	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n\n\n\n\n");
		printf("   �ּҷ� Version 0.05-�����ϱ�\n");
		printf("   =========================================\n");
		printf("   ��      �� : "); rewind(stdin); scanf("%s", name);
		printf("   ��      �� : "); rewind(stdin); gets(address);
		printf("   ��ȭ  ��ȣ : "); rewind(stdin); scanf("%s", phoneNumber);
		printf("   �̸����ּ� : "); rewind(stdin); scanf("%s", emailAddress);
		printf("   -----------------------------------------\n");
		printf("   �����Ͻðڽ��ϱ�?(Yes/No)"); rewind(stdin); recording = getchar();
		if (recording == 'Y' || recording == 'y') {
			index = Record(addressBook, name, address, phoneNumber, emailAddress);
			if (index != -1) {
				printf("   =========================================\n");
				printf("   ��ȣ    ����\t�ּ�\t\t\t��ȭ��ȣ\t�̸����ּ�\n");
				printf("   -----------------------------------------\n");
				printf("   %d    %s\t%s\t\t\t%s\t%s\n", index + 1, addressBook->personals[index].name, addressBook->personals[index].address,
					addressBook->personals[index].phoneNumber, addressBook->personals[index].emailAddress);
			}
			
		}
		printf("   =========================================\n");
		printf("   ����Ͻðڽ��ϱ�?(yes/no) "); rewind(stdin); going = getchar();
	}
}

void FormForFinding(AddressBook* addressBook) {
	char name[11];
	char going = 'y';
	Long i;
	Long count;
	Long (*indexes);
	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n\n\n\n\n\n");
		printf("   �ּҷ� Version 0.05-ã��\n");
		printf("   =========================================\n");
		printf("   ��      �� : "); rewind(stdin); scanf("%s", name);
		printf("   =========================================\n");
		printf("   ��ȣ    ����\t\t\t�ּ�\t��ȭ��ȣ\t�̸����ּ�\n");
		printf("   -----------------------------------------\n");
		Find(addressBook, name, &indexes, &count);
		i = 0;
		while (i < count) {
			printf("   %d    %s\t%s\t\t\t%s\t%s\n", indexes[i] + 1, addressBook->personals[indexes[i]].name,
				addressBook->personals[indexes[i]].address, addressBook->personals[indexes[i]].phoneNumber, addressBook->personals[indexes[i]].emailAddress);
			i++;
		}
		if (indexes != NULL) {
			free(indexes);
		}
		printf("   =========================================\n");
		printf("   ����Ͻðڽ��ϱ�?(yes/no) "); rewind(stdin); going = getchar();
	}
}

void FormForCorrecting(AddressBook* addressBook) {
	char name[11];
	char address[64];
	char phoneNumber[12];
	char emailAddress[64];
	char correcting;
	char going = 'Y';
	Long index;
	Long number;
	Long count;
	Long (*indexes);
	Long i;
	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n\n\n");
		printf("   �ּҷ� Version 0.05-��ġ��\n");
		printf("   =========================================\n");
		printf("   ��      �� : "); rewind(stdin); scanf("%s", name);
		printf("   =========================================\n");
		printf("   ��ȣ    ����\t\t\t�ּ�\t��ȭ��ȣ\t�̸����ּ�\n");
		printf("   -----------------------------------------\n");
		Find(addressBook, name, &indexes, &count);
		i = 0;
		while (i < count) {
			printf("   %d    %s\t%s\t\t\t%s\t%s\n", i + 1, addressBook->personals[indexes[i]].name,
				addressBook->personals[indexes[i]].address, addressBook->personals[indexes[i]].phoneNumber, addressBook->personals[indexes[i]].emailAddress);
			i++;
		}
		if (count > 0) {
			printf("   -----------------------------------------\n");
			printf("   ��      ȣ : "); rewind(stdin); scanf("%d", &number);
			printf("   -----------------------------------------\n");
			printf("   ��      �� : %s", addressBook->personals[indexes[number-1]].address); rewind(stdin); gets(address);
			if (strcmp(address, "") == 0) {
				strcpy(address, addressBook->personals[indexes[number - 1]].address);
			}
			printf("   ��ȭ  ��ȣ : %s", addressBook->personals[indexes[number - 1]].phoneNumber); rewind(stdin); gets(phoneNumber);
			if (strcmp(phoneNumber, "") == 0) {
				strcpy(phoneNumber, addressBook->personals[indexes[number - 1]].phoneNumber);
			}
			printf("   �̸����ּ� : %s", addressBook->personals[indexes[number - 1]].emailAddress); rewind(stdin); gets(emailAddress);
			if (strcmp(emailAddress, "") == 0) {
				strcpy(emailAddress, addressBook->personals[indexes[number - 1]].emailAddress);
			}
			printf("   -----------------------------------------\n");
			printf("   ��ġ�ðڽ��ϱ�?(Yes/No)"); rewind(stdin); correcting = getchar();
			if (correcting == 'Y' || correcting == 'y') {
				index = number;
				index = Correct(addressBook, indexes[number-1], address, phoneNumber, emailAddress);
				printf("  =========================================\n");
				printf("  ��ȣ    ����\t�ּ�\t\t\t��ȭ��ȣ\t�̸����ּ�\n");
				printf("  -----------------------------------------\n");
				printf("  %d    %s\t%s\t\t\t%s\t%s\n", index + 1, addressBook->personals[index].name, addressBook->personals[index].address,
					addressBook->personals[index].phoneNumber, addressBook->personals[index].emailAddress);
			}
		}
		if (indexes != NULL) {
			free(indexes);
		}
		printf("   =========================================\n");
		printf("   ����Ͻðڽ��ϱ�?(yes/no) "); rewind(stdin); going = getchar();
	}
}

void FormForErasing(AddressBook* addressBook) {
	char name[11];
	char erasing;
	char going = 'Y';
	Long index;
	Long number;
	Long (*indexes);
	Long count;
	Long i;
	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n\n\n");
		printf("    �ּҷ� Version 0.05-�����\n");
		printf("    =========================================\n");
		printf("    ��      �� : "); rewind(stdin); scanf("%s", name);
		printf("    =========================================\n");
		printf("    ��ȣ    ����\t\t\t�ּ�\t��ȭ��ȣ\t�̸����ּ�\n");
		printf("    -----------------------------------------\n");
		Find(addressBook, name, &indexes, &count);
		i = 0;
		while (i < count) {
			printf("    %d    %s\t%s\t\t\t%s\t%s\n", i + 1, addressBook->personals[indexes[i]].name,
				addressBook->personals[indexes[i]].address, addressBook->personals[indexes[i]].phoneNumber, addressBook->personals[indexes[i]].emailAddress);
			i++;
		}
		if (count > 0) {
			printf("    -----------------------------------------\n");
			printf("    ��      ȣ : "); rewind(stdin); scanf("%d", &number);
			printf("    =========================================\n");
			printf("    ��ȣ    ����\t�ּ�\t\t\t��ȭ��ȣ\t�̸����ּ�\n");
			printf("    -----------------------------------------\n");
			printf("    %d    %s\t%s\t\t\t%s\t%s\n", indexes[number-1] + 1, addressBook->personals[indexes[number - 1]].name,
				addressBook->personals[indexes[number - 1]].address, addressBook->personals[indexes[number - 1]].phoneNumber, addressBook->personals[indexes[number - 1]].emailAddress);
			printf("    -----------------------------------------\n");
			printf("    ����ðڽ��ϱ�?(Yes/No)"); rewind(stdin); erasing = getchar();
			if (erasing == 'Y' || erasing == 'y') {
				index = number;
				index = Erase(addressBook, indexes[number-1]);
				if (index == -1) {
					printf("    =========================================\n");
					printf("    ���������ϴ�\n");
				}
			}
		}
		if (indexes != NULL) {
			free(indexes);
		}
		printf("    =========================================\n");
		printf("    ����Ͻðڽ��ϱ�?(yes/no) "); rewind(stdin); going = getchar();
	}
}

void FormForArranging(AddressBook* addressBook) {
	char going;
	Long i = 0;
	Long j;
	while (i < addressBook->length) {
		system("cls");
		printf("\n\n\n\n");
		printf("    �ּҷ� Version 0.05-�����ϱ�\n");
		printf("    =========================================\n");
		printf("    ��ȣ    ����\t�ּ�\t\t\t��ȭ��ȣ\t�̸����ּ�\n");
		printf("    -----------------------------------------\n");
		Arrange(addressBook);
		j = 1;
		while (j <= 10 && i < addressBook->length) {
			printf("    %d    %s\t%s\t\t\t%s\t%s\n", i + 1, addressBook->personals[i].name, addressBook->personals[i].address,
				addressBook->personals[i].phoneNumber, addressBook->personals[i].emailAddress);
			j++;
			i++;
		}
		printf("    =========================================\n");
		printf("    �ƹ�Ű�� ��������"); rewind(stdin); going = getchar();
	}
}

void FormForShowAll(AddressBook* addressBook) {
	char going;
	Long i = 0;
	Long j;
	while (i < addressBook->length) {
		system("cls");
		printf("\n\n\n\n");
		printf("    �ּҷ� Version 0.05-��ü����\n");
		printf("    =========================================\n");
		printf("    ��ȣ    ����\t�ּ�\t\t\t��ȭ��ȣ\t�̸����ּ�\n");
		printf("    -----------------------------------------\n");
		j = 1;
		while (j <= 10 && i < addressBook->length) {
			printf("    %d    %s\t%s\t\t\t%s\t%s\n", i + 1, addressBook->personals[i].name, addressBook->personals[i].address,
				addressBook->personals[i].phoneNumber, addressBook->personals[i].emailAddress);
			j++;
			i++;
		}
		printf("    =========================================\n");
		printf("    �ƹ�Ű�� ��������"); rewind(stdin); going = getchar();
	}
}