#include "form.h"
#include "wordBook.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

int main(int argc, char* argv[]) {
	WordBook wordBook = { {{"","","",""}, {"","","",""}, {"","","",""}, {"","","",""}, {"","","",""}, {"","","",""}}, MAX, 0 };
	int menu;
	Load(&wordBook);
	DisplayMenu();
	rewind(stdin); scanf("%d", &menu);
	while (menu != 0) {
		switch (menu) {
			case 1: FormForRecording(&wordBook); break;
			case 2: FindMenu(&wordBook);  break;
			case 3: FormForCorrecting(&wordBook); break;
			case 4: FormForErasing(&wordBook); break;
			case 5: FormForArranging(&wordBook); break;
			case 6: FormForShowAll(&wordBook); break;
			default: break;
		}
		DisplayMenu();
		rewind(stdin); scanf("%d", &menu);
	}
	Save(&wordBook);
	return 0;
}

void FindMenu(WordBook* wordBook) {
	int findMenu;
	DisplayFindMenu();
	rewind(stdin); scanf("%d", &findMenu);
	while (findMenu != 0) {
		switch (findMenu) {
			case 1: FormForFindSpelling(wordBook); break;
			case 2: FormForFindMeaning(wordBook); break;
			case 0: DisplayMenu(); break;
			default: break;
		}
		DisplayFindMenu();
		rewind(stdin); scanf("%d", &findMenu);
	}
}

//�ܾ��� �޴�����
void DisplayMenu() {
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t     �ܾ��� Version 0.05\n");
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

//ã�� �޴�����
void DisplayFindMenu() {
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t     �ܾ��� Version 0.05-ã��\n");
	printf("\t\t\t     =========================================\n");
	printf("\t\t\t     [1] ö��ã��\n");
	printf("\t\t\t     [2] �ǹ�ã��\n");
	printf("\t\t\t     [0] ���ư���\n");
	printf("\t\t\t     -----------------------------------------\n");
	printf("\t\t\t     �޴��� �����Ͻʽÿ�! ");
}

//�ܾ��� ����
void FormForRecording(WordBook* wordBook) {
	char spelling[64];
	char wordClass[11];
	char meaning[64];
	char example[128];
	char recording;
	char going = 'Y';
	Long index;
	Long number;
	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n\n\n\n\n");
		printf("    �ܾ��� Version 0.05-�����ϱ�\n");
		printf("    ============================================================================\n");
		printf("    ö�ڵ� : "); rewind(stdin); scanf("%s", spelling);
		printf("\n");
		printf("    [1] ��� [2] ���� [3] ���� [4] �����\n");
		printf("    [5] �λ� [6] ��ġ�� [7] ���ӻ� [8] ��ź��\n");
		printf("\n");
		printf("    ǰ  �� : "); rewind(stdin); scanf("%d", &number);
		switch (number) {
		case 1: strcpy(wordClass, "���"); break;
		case 2: strcpy(wordClass, "����"); break;
		case 3: strcpy(wordClass, "����"); break;
		case 4: strcpy(wordClass, "�����"); break;
		case 5: strcpy(wordClass, "�λ�"); break;
		case 6: strcpy(wordClass, "��ġ��"); break;
		case 7: strcpy(wordClass, "���ӻ�"); break;
		case 8: strcpy(wordClass, "��ź��"); break;
		default: break;
		}
		printf("    ��  �� : "); rewind(stdin); scanf("%s", meaning);
		printf("    ��  �� : "); rewind(stdin); gets(example);
		printf("    ----------------------------------------------------------------------------\n");
		printf("    �����Ͻðڽ��ϱ�?(Yes/No)"); rewind(stdin); recording = getchar();
		if (recording == 'Y' || recording == 'y') {
			index = Record(wordBook, spelling, wordClass, meaning, example);

			if (index != -1) {
				printf("    ============================================================================\n");
				printf("    ��ȣ ö�ڵ�     ǰ��             �ǹ�             ����                      \n");
				printf("    ----------------------------------------------------------------------------\n");
				printf("    %-4d %-10s %-16s %-16s %-16s\n", index + 1, wordBook->words[index].spelling, wordBook->words[index].wordClass,
					wordBook->words[index].meaning, wordBook->words[index].example);
			}
		}
		printf("    ============================================================================\n");
		printf("   ����Ͻðڽ��ϱ�?(yes/no) "); rewind(stdin); going = getchar();
	}
}

//�ܾ��� ö�� ã��
void FormForFindSpelling(WordBook* wordBook) {
	char spelling[64];
	char going = 'Y';
	Long i;
	Long count;
	Long indexes[MAX];
	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n\n\n\n\n\n\n\n");
		printf("    �ܾ��� Version 0.05-ö��ã��\n");
		printf("    ============================================================================\n");
		printf("    ö�ڵ� : "); rewind(stdin); scanf("%s", spelling);
		printf("    ============================================================================\n");
		FindSpelling(wordBook, spelling, indexes, &count);
		printf("    ��ȣ ö�ڵ�     ǰ��             �ǹ�             ����                      \n");
		printf("    ----------------------------------------------------------------------------\n");
		i = 0;
		while (i < count) {
			printf("   %-4d %-10s %-16s %-16s %-16s\n", i + 1, wordBook->words[indexes[i]].spelling,
				wordBook->words[indexes[i]].wordClass, wordBook->words[indexes[i]].meaning, wordBook->words[indexes[i]].example);
			i++;
		}
		printf("    ============================================================================\n");
		printf("   ����Ͻðڽ��ϱ�?(yes/no) "); rewind(stdin); going = getchar();
	}
}

//�ܾ��� �ǹ� ã��
void FormForFindMeaning(WordBook* wordBook) {
	char meaning[64];
	char going = 'Y';
	Long i;
	Long count;
	Long indexes[MAX];
	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n\n\n\n\n\n\n\n");
		printf("    �ܾ��� Version 0.05-�ǹ�ã��\n");
		printf("    ============================================================================\n");
		printf("    ��  �� : "); rewind(stdin); scanf("%s", meaning);
		printf("    ============================================================================\n");
		FindMeaning(wordBook, meaning, indexes, &count);
		printf("    ��ȣ �ǹ�             ǰ��             ö�ڵ�     ����                      \n");
		printf("    ----------------------------------------------------------------------------\n");
		i = 0;
		while (i < count) {
			printf("   %-4d %-16s %-16s %-10s %-16s\n", i + 1, wordBook->words[indexes[i]].meaning,
				wordBook->words[indexes[i]].wordClass, wordBook->words[indexes[i]].spelling, wordBook->words[indexes[i]].example);
			i++;
		}
		printf("    ============================================================================\n");
		printf("   ����Ͻðڽ��ϱ�?(yes/no) "); rewind(stdin); going = getchar();
	}
}

//�ܾ��� ��ġ��
void FormForCorrecting(WordBook* wordBook) {
	char spelling[64];
	char wordClass[11];
	char meaning[64];
	char example[128];
	char correcting;
	char going = 'Y';
	Long index;
	Long number;
	Long count;
	Long indexes[MAX];
	Long i;
	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n\n\n");
		printf("    �ܾ��� Version 0.05-��ġ��\n");
		printf("    ============================================================================\n");
		printf("    ö�ڵ� : "); rewind(stdin); scanf("%s", spelling);
		printf("    ============================================================================\n");
		printf("    ��ȣ ö�ڵ�     ǰ��             �ǹ�             ����                      \n");
		printf("    ----------------------------------------------------------------------------\n");
		FindSpelling(wordBook, spelling, indexes, &count);
		i = 0;
		while (i < count) {
			printf("   %-4d %-10s %-16s %-16s %-16s\n", i + 1, wordBook->words[indexes[i]].spelling,
				wordBook->words[indexes[i]].wordClass, wordBook->words[indexes[i]].meaning, wordBook->words[indexes[i]].example);
			i++;
		}
		if (count > 0) {
			printf("    ----------------------------------------------------------------------------\n");
			printf("    ��  ȣ : "); rewind(stdin); scanf("%d", &number);
			printf("    ----------------------------------------------------------------------------\n");
			printf("    ǰ  �� : %s", wordBook->words[indexes[number - 1]].wordClass); rewind(stdin); gets(wordClass);
			if (strcmp(wordClass, "") == 0) {
				strcpy(wordClass, wordBook->words[indexes[number - 1]].wordClass);
			}
			printf("    ��  �� : %s", wordBook->words[indexes[number - 1]].meaning); rewind(stdin); gets(meaning);
			if (strcmp(meaning, "") == 0) {
				strcpy(meaning, wordBook->words[indexes[number - 1]].meaning);
			}
			printf("    ��  �� : %s", wordBook->words[indexes[number - 1]].example); rewind(stdin); gets(example);
			if (strcmp(example, "") == 0) {
				strcpy(example, wordBook->words[indexes[number - 1]].example);
			}
			printf("    ============================================================================\n");
			printf("    ��ġ�ðڽ��ϱ�?(Yes/No)"); rewind(stdin); correcting = getchar();
			if (correcting == 'Y' || correcting == 'y') {
				index = number;
				index = Correct(wordBook, indexes[number - 1], wordClass, meaning, example);
				printf("    ============================================================================\n");
				printf("    ��ȣ ö�ڵ�     ǰ��             �ǹ�             ����                      \n");
				printf("    ----------------------------------------------------------------------------\n");
				printf("    %-4d %-10s %-16s %-16s %-16s\n", index + 1, wordBook->words[index].spelling, wordBook->words[index].wordClass,
					wordBook->words[index].meaning, wordBook->words[index].example);
			}
		}
		printf("    ============================================================================\n");
		printf("    ����Ͻðڽ��ϱ�?(yes/no) "); rewind(stdin); going = getchar();
	}
}

//�ܾ��� �����
void FormForErasing(WordBook* wordBook) {
	char spelling[64];
	char erasing;
	char going = 'Y';
	Long index;
	Long number;
	Long count;
	Long indexes[MAX];
	Long i;
	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n\n\n");
		printf("    �ܾ��� Version 0.05-�����\n");
		printf("    ============================================================================\n");
		printf("    ö�ڵ� : "); rewind(stdin); scanf("%s", spelling);
		printf("    ============================================================================\n");
		printf("    ��ȣ ö�ڵ�     ǰ��             �ǹ�             ����                      \n");
		printf("    ----------------------------------------------------------------------------\n");
		FindSpelling(wordBook, spelling, indexes, &count);
		i = 0;
		while (i < count) {
			printf("   %-4d %-10s %-16s %-16s %-16s\n", i + 1, wordBook->words[indexes[i]].spelling,
				wordBook->words[indexes[i]].wordClass, wordBook->words[indexes[i]].meaning, wordBook->words[indexes[i]].example);
			i++;
		}
			if (count > 0) {
				printf("    ============================================================================\n");
				printf("    ��  ȣ : "); rewind(stdin); scanf("%d", &number);
				printf("    ============================================================================\n");
				printf("    ��ȣ ö�ڵ�     ǰ��             �ǹ�             ����                      \n");
				printf("    ----------------------------------------------------------------------------\n");
				printf("    %-4d %-10s %-16s %-16s %-16s\n", indexes[number - 1] + 1, wordBook->words[indexes[number - 1]].spelling,
					wordBook->words[indexes[number - 1]].wordClass, wordBook->words[indexes[number - 1]].meaning, wordBook->words[indexes[number - 1]].example);
				printf("    ----------------------------------------------------------------------------\n");
				printf("    ����ðڽ��ϱ�?(Yes/No)"); rewind(stdin); erasing = getchar();
				if (erasing == 'Y' || erasing == 'y') {
					index = number;
					index = Erase(wordBook, indexes[number - 1]);
					if (index == -1) {
						printf("    ============================================================================\n");
						printf("    ���������ϴ�\n");
					}
				}
			}
			printf("    ============================================================================\n");
			printf("    ����Ͻðڽ��ϱ�?(yes/no) "); rewind(stdin); going = getchar();
		}
}

//�ܾ��� �����ϱ�
void FormForArranging(WordBook* wordBook) {
	Long i = 0;
	Long j;
	while (i < wordBook->length) {
		system("cls");
		printf("\n\n\n\n");
		printf("    �ܾ��� Version 0.05-�����ϱ�\n");
		printf("    ============================================================================\n");
		printf("    ��ȣ ö�ڵ�     ǰ��             �ǹ�             ����                      \n");
		printf("    ----------------------------------------------------------------------------\n");
		Arrange(wordBook);
		j = 1;
		while (j <= 10 && i < wordBook->length) {
			printf("    %-4d %-10s %-16s %-16s %-16s\n", i + 1, wordBook->words[i].spelling, wordBook->words[i].wordClass,
				wordBook->words[i].meaning, wordBook->words[i].example);
			j++;
			i++;
		}
		printf("    ============================================================================\n");
		printf("    �ƹ�Ű�� ��������"); rewind(stdin); getchar();
	}
}

//�ܾ��� ��ü���� 
void FormForShowAll(WordBook* wordBook) {
	Long i = 0;
	Long j;
	while (i <wordBook->length) {
		system("cls");
		printf("\n\n\n\n");
		printf("    �ܾ��� Version 0.05-��ü����\n");
		printf("    ============================================================================\n");
		printf("    ��ȣ ö�ڵ�     ǰ��             �ǹ�             ����                      \n");
		printf("    ----------------------------------------------------------------------------\n");
		j = 1;
		while (j <= 10 && i < wordBook->length) {
			printf("    %-4d %-10s %-16s %-16s %-16s\n", i + 1, wordBook->words[i].spelling, wordBook->words[i].wordClass,
				wordBook->words[i].meaning, wordBook->words[i].example);
			j++;
			i++;
		}
		printf("    ============================================================================\n");
		printf("    �ƹ�Ű�� ��������"); rewind(stdin); getchar();
	}
}