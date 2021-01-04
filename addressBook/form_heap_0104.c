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
	printf("\t\t\t     주소록 Version 0.05\n");
	printf("\t\t\t     =========================================\n");
	printf("\t\t\t     [1] 기재하기\n");
	printf("\t\t\t     [2] 찾    기\n");
	printf("\t\t\t     [3] 고 치 기\n");
	printf("\t\t\t     [4] 지 우 기\n");
	printf("\t\t\t     [5] 정리하기\n");
	printf("\t\t\t     [6] 전체보기\n");
	printf("\t\t\t     [0] 끝 내 기\n");
	printf("\t\t\t     -----------------------------------------\n");
	printf("\t\t\t     메뉴를 선택하십시오! ");
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
		printf("   주소록 Version 0.05-기재하기\n");
		printf("   =========================================\n");
		printf("   성      명 : "); rewind(stdin); scanf("%s", name);
		printf("   주      소 : "); rewind(stdin); gets(address);
		printf("   전화  번호 : "); rewind(stdin); scanf("%s", phoneNumber);
		printf("   이메일주소 : "); rewind(stdin); scanf("%s", emailAddress);
		printf("   -----------------------------------------\n");
		printf("   기재하시겠습니까?(Yes/No)"); rewind(stdin); recording = getchar();
		if (recording == 'Y' || recording == 'y') {
			index = Record(addressBook, name, address, phoneNumber, emailAddress);
			if (index != -1) {
				printf("   =========================================\n");
				printf("   번호    성명\t주소\t\t\t전화번호\t이메일주소\n");
				printf("   -----------------------------------------\n");
				printf("   %d    %s\t%s\t\t\t%s\t%s\n", index + 1, addressBook->personals[index].name, addressBook->personals[index].address,
					addressBook->personals[index].phoneNumber, addressBook->personals[index].emailAddress);
			}
			
		}
		printf("   =========================================\n");
		printf("   계속하시겠습니까?(yes/no) "); rewind(stdin); going = getchar();
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
		printf("   주소록 Version 0.05-찾기\n");
		printf("   =========================================\n");
		printf("   성      명 : "); rewind(stdin); scanf("%s", name);
		printf("   =========================================\n");
		printf("   번호    성명\t\t\t주소\t전화번호\t이메일주소\n");
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
		printf("   계속하시겠습니까?(yes/no) "); rewind(stdin); going = getchar();
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
		printf("   주소록 Version 0.05-고치기\n");
		printf("   =========================================\n");
		printf("   성      명 : "); rewind(stdin); scanf("%s", name);
		printf("   =========================================\n");
		printf("   번호    성명\t\t\t주소\t전화번호\t이메일주소\n");
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
			printf("   번      호 : "); rewind(stdin); scanf("%d", &number);
			printf("   -----------------------------------------\n");
			printf("   주      소 : %s", addressBook->personals[indexes[number-1]].address); rewind(stdin); gets(address);
			if (strcmp(address, "") == 0) {
				strcpy(address, addressBook->personals[indexes[number - 1]].address);
			}
			printf("   전화  번호 : %s", addressBook->personals[indexes[number - 1]].phoneNumber); rewind(stdin); gets(phoneNumber);
			if (strcmp(phoneNumber, "") == 0) {
				strcpy(phoneNumber, addressBook->personals[indexes[number - 1]].phoneNumber);
			}
			printf("   이메일주소 : %s", addressBook->personals[indexes[number - 1]].emailAddress); rewind(stdin); gets(emailAddress);
			if (strcmp(emailAddress, "") == 0) {
				strcpy(emailAddress, addressBook->personals[indexes[number - 1]].emailAddress);
			}
			printf("   -----------------------------------------\n");
			printf("   고치시겠습니까?(Yes/No)"); rewind(stdin); correcting = getchar();
			if (correcting == 'Y' || correcting == 'y') {
				index = number;
				index = Correct(addressBook, indexes[number-1], address, phoneNumber, emailAddress);
				printf("  =========================================\n");
				printf("  번호    성명\t주소\t\t\t전화번호\t이메일주소\n");
				printf("  -----------------------------------------\n");
				printf("  %d    %s\t%s\t\t\t%s\t%s\n", index + 1, addressBook->personals[index].name, addressBook->personals[index].address,
					addressBook->personals[index].phoneNumber, addressBook->personals[index].emailAddress);
			}
		}
		if (indexes != NULL) {
			free(indexes);
		}
		printf("   =========================================\n");
		printf("   계속하시겠습니까?(yes/no) "); rewind(stdin); going = getchar();
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
		printf("    주소록 Version 0.05-지우기\n");
		printf("    =========================================\n");
		printf("    성      명 : "); rewind(stdin); scanf("%s", name);
		printf("    =========================================\n");
		printf("    번호    성명\t\t\t주소\t전화번호\t이메일주소\n");
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
			printf("    번      호 : "); rewind(stdin); scanf("%d", &number);
			printf("    =========================================\n");
			printf("    번호    성명\t주소\t\t\t전화번호\t이메일주소\n");
			printf("    -----------------------------------------\n");
			printf("    %d    %s\t%s\t\t\t%s\t%s\n", indexes[number-1] + 1, addressBook->personals[indexes[number - 1]].name,
				addressBook->personals[indexes[number - 1]].address, addressBook->personals[indexes[number - 1]].phoneNumber, addressBook->personals[indexes[number - 1]].emailAddress);
			printf("    -----------------------------------------\n");
			printf("    지우시겠습니까?(Yes/No)"); rewind(stdin); erasing = getchar();
			if (erasing == 'Y' || erasing == 'y') {
				index = number;
				index = Erase(addressBook, indexes[number-1]);
				if (index == -1) {
					printf("    =========================================\n");
					printf("    지워졌습니다\n");
				}
			}
		}
		if (indexes != NULL) {
			free(indexes);
		}
		printf("    =========================================\n");
		printf("    계속하시겠습니까?(yes/no) "); rewind(stdin); going = getchar();
	}
}

void FormForArranging(AddressBook* addressBook) {
	char going;
	Long i = 0;
	Long j;
	while (i < addressBook->length) {
		system("cls");
		printf("\n\n\n\n");
		printf("    주소록 Version 0.05-정리하기\n");
		printf("    =========================================\n");
		printf("    번호    성명\t주소\t\t\t전화번호\t이메일주소\n");
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
		printf("    아무키나 누르세요"); rewind(stdin); going = getchar();
	}
}

void FormForShowAll(AddressBook* addressBook) {
	char going;
	Long i = 0;
	Long j;
	while (i < addressBook->length) {
		system("cls");
		printf("\n\n\n\n");
		printf("    주소록 Version 0.05-전체보기\n");
		printf("    =========================================\n");
		printf("    번호    성명\t주소\t\t\t전화번호\t이메일주소\n");
		printf("    -----------------------------------------\n");
		j = 1;
		while (j <= 10 && i < addressBook->length) {
			printf("    %d    %s\t%s\t\t\t%s\t%s\n", i + 1, addressBook->personals[i].name, addressBook->personals[i].address,
				addressBook->personals[i].phoneNumber, addressBook->personals[i].emailAddress);
			j++;
			i++;
		}
		printf("    =========================================\n");
		printf("    아무키나 누르세요"); rewind(stdin); going = getchar();
	}
}