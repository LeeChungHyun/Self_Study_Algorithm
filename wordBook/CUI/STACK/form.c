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

//단어장 메뉴설계
void DisplayMenu() {
	system("cls");
	printf("\n\n\n\n\n\n");
	printf("\t\t\t     단어장 Version 0.05\n");
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

//찾기 메뉴설계
void DisplayFindMenu() {
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t     단어장 Version 0.05-찾기\n");
	printf("\t\t\t     =========================================\n");
	printf("\t\t\t     [1] 철자찾기\n");
	printf("\t\t\t     [2] 의미찾기\n");
	printf("\t\t\t     [0] 돌아가기\n");
	printf("\t\t\t     -----------------------------------------\n");
	printf("\t\t\t     메뉴를 선택하십시오! ");
}

//단어장 기재
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
		printf("    단어장 Version 0.05-기재하기\n");
		printf("    ============================================================================\n");
		printf("    철자들 : "); rewind(stdin); scanf("%s", spelling);
		printf("\n");
		printf("    [1] 명사 [2] 대명사 [3] 동사 [4] 형용사\n");
		printf("    [5] 부사 [6] 전치사 [7] 접속사 [8] 감탄사\n");
		printf("\n");
		printf("    품  사 : "); rewind(stdin); scanf("%d", &number);
		switch (number) {
		case 1: strcpy(wordClass, "명사"); break;
		case 2: strcpy(wordClass, "대명사"); break;
		case 3: strcpy(wordClass, "동사"); break;
		case 4: strcpy(wordClass, "형용사"); break;
		case 5: strcpy(wordClass, "부사"); break;
		case 6: strcpy(wordClass, "전치사"); break;
		case 7: strcpy(wordClass, "접속사"); break;
		case 8: strcpy(wordClass, "감탄사"); break;
		default: break;
		}
		printf("    의  미 : "); rewind(stdin); scanf("%s", meaning);
		printf("    예  시 : "); rewind(stdin); gets(example);
		printf("    ----------------------------------------------------------------------------\n");
		printf("    기재하시겠습니까?(Yes/No)"); rewind(stdin); recording = getchar();
		if (recording == 'Y' || recording == 'y') {
			index = Record(wordBook, spelling, wordClass, meaning, example);

			if (index != -1) {
				printf("    ============================================================================\n");
				printf("    번호 철자들     품사             의미             예시                      \n");
				printf("    ----------------------------------------------------------------------------\n");
				printf("    %-4d %-10s %-16s %-16s %-16s\n", index + 1, wordBook->words[index].spelling, wordBook->words[index].wordClass,
					wordBook->words[index].meaning, wordBook->words[index].example);
			}
		}
		printf("    ============================================================================\n");
		printf("   계속하시겠습니까?(yes/no) "); rewind(stdin); going = getchar();
	}
}

//단어장 철자 찾기
void FormForFindSpelling(WordBook* wordBook) {
	char spelling[64];
	char going = 'Y';
	Long i;
	Long count;
	Long indexes[MAX];
	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n\n\n\n\n\n\n\n");
		printf("    단어장 Version 0.05-철자찾기\n");
		printf("    ============================================================================\n");
		printf("    철자들 : "); rewind(stdin); scanf("%s", spelling);
		printf("    ============================================================================\n");
		FindSpelling(wordBook, spelling, indexes, &count);
		printf("    번호 철자들     품사             의미             예시                      \n");
		printf("    ----------------------------------------------------------------------------\n");
		i = 0;
		while (i < count) {
			printf("   %-4d %-10s %-16s %-16s %-16s\n", i + 1, wordBook->words[indexes[i]].spelling,
				wordBook->words[indexes[i]].wordClass, wordBook->words[indexes[i]].meaning, wordBook->words[indexes[i]].example);
			i++;
		}
		printf("    ============================================================================\n");
		printf("   계속하시겠습니까?(yes/no) "); rewind(stdin); going = getchar();
	}
}

//단어장 의미 찾기
void FormForFindMeaning(WordBook* wordBook) {
	char meaning[64];
	char going = 'Y';
	Long i;
	Long count;
	Long indexes[MAX];
	while (going == 'Y' || going == 'y') {
		system("cls");
		printf("\n\n\n\n\n\n\n\n");
		printf("    단어장 Version 0.05-의미찾기\n");
		printf("    ============================================================================\n");
		printf("    의  미 : "); rewind(stdin); scanf("%s", meaning);
		printf("    ============================================================================\n");
		FindMeaning(wordBook, meaning, indexes, &count);
		printf("    번호 의미             품사             철자들     예시                      \n");
		printf("    ----------------------------------------------------------------------------\n");
		i = 0;
		while (i < count) {
			printf("   %-4d %-16s %-16s %-10s %-16s\n", i + 1, wordBook->words[indexes[i]].meaning,
				wordBook->words[indexes[i]].wordClass, wordBook->words[indexes[i]].spelling, wordBook->words[indexes[i]].example);
			i++;
		}
		printf("    ============================================================================\n");
		printf("   계속하시겠습니까?(yes/no) "); rewind(stdin); going = getchar();
	}
}

//단어장 고치기
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
		printf("    단어장 Version 0.05-고치기\n");
		printf("    ============================================================================\n");
		printf("    철자들 : "); rewind(stdin); scanf("%s", spelling);
		printf("    ============================================================================\n");
		printf("    번호 철자들     품사             의미             예시                      \n");
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
			printf("    번  호 : "); rewind(stdin); scanf("%d", &number);
			printf("    ----------------------------------------------------------------------------\n");
			printf("    품  사 : %s", wordBook->words[indexes[number - 1]].wordClass); rewind(stdin); gets(wordClass);
			if (strcmp(wordClass, "") == 0) {
				strcpy(wordClass, wordBook->words[indexes[number - 1]].wordClass);
			}
			printf("    의  미 : %s", wordBook->words[indexes[number - 1]].meaning); rewind(stdin); gets(meaning);
			if (strcmp(meaning, "") == 0) {
				strcpy(meaning, wordBook->words[indexes[number - 1]].meaning);
			}
			printf("    예  시 : %s", wordBook->words[indexes[number - 1]].example); rewind(stdin); gets(example);
			if (strcmp(example, "") == 0) {
				strcpy(example, wordBook->words[indexes[number - 1]].example);
			}
			printf("    ============================================================================\n");
			printf("    고치시겠습니까?(Yes/No)"); rewind(stdin); correcting = getchar();
			if (correcting == 'Y' || correcting == 'y') {
				index = number;
				index = Correct(wordBook, indexes[number - 1], wordClass, meaning, example);
				printf("    ============================================================================\n");
				printf("    번호 철자들     품사             의미             예시                      \n");
				printf("    ----------------------------------------------------------------------------\n");
				printf("    %-4d %-10s %-16s %-16s %-16s\n", index + 1, wordBook->words[index].spelling, wordBook->words[index].wordClass,
					wordBook->words[index].meaning, wordBook->words[index].example);
			}
		}
		printf("    ============================================================================\n");
		printf("    계속하시겠습니까?(yes/no) "); rewind(stdin); going = getchar();
	}
}

//단어장 지우기
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
		printf("    단어장 Version 0.05-지우기\n");
		printf("    ============================================================================\n");
		printf("    철자들 : "); rewind(stdin); scanf("%s", spelling);
		printf("    ============================================================================\n");
		printf("    번호 철자들     품사             의미             예시                      \n");
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
				printf("    번  호 : "); rewind(stdin); scanf("%d", &number);
				printf("    ============================================================================\n");
				printf("    번호 철자들     품사             의미             예시                      \n");
				printf("    ----------------------------------------------------------------------------\n");
				printf("    %-4d %-10s %-16s %-16s %-16s\n", indexes[number - 1] + 1, wordBook->words[indexes[number - 1]].spelling,
					wordBook->words[indexes[number - 1]].wordClass, wordBook->words[indexes[number - 1]].meaning, wordBook->words[indexes[number - 1]].example);
				printf("    ----------------------------------------------------------------------------\n");
				printf("    지우시겠습니까?(Yes/No)"); rewind(stdin); erasing = getchar();
				if (erasing == 'Y' || erasing == 'y') {
					index = number;
					index = Erase(wordBook, indexes[number - 1]);
					if (index == -1) {
						printf("    ============================================================================\n");
						printf("    지워졌습니다\n");
					}
				}
			}
			printf("    ============================================================================\n");
			printf("    계속하시겠습니까?(yes/no) "); rewind(stdin); going = getchar();
		}
}

//단어장 정리하기
void FormForArranging(WordBook* wordBook) {
	Long i = 0;
	Long j;
	while (i < wordBook->length) {
		system("cls");
		printf("\n\n\n\n");
		printf("    단어장 Version 0.05-정리하기\n");
		printf("    ============================================================================\n");
		printf("    번호 철자들     품사             의미             예시                      \n");
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
		printf("    아무키나 누르세요"); rewind(stdin); getchar();
	}
}

//단어장 전체보기 
void FormForShowAll(WordBook* wordBook) {
	Long i = 0;
	Long j;
	while (i <wordBook->length) {
		system("cls");
		printf("\n\n\n\n");
		printf("    단어장 Version 0.05-전체보기\n");
		printf("    ============================================================================\n");
		printf("    번호 철자들     품사             의미             예시                      \n");
		printf("    ----------------------------------------------------------------------------\n");
		j = 1;
		while (j <= 10 && i < wordBook->length) {
			printf("    %-4d %-10s %-16s %-16s %-16s\n", i + 1, wordBook->words[i].spelling, wordBook->words[i].wordClass,
				wordBook->words[i].meaning, wordBook->words[i].example);
			j++;
			i++;
		}
		printf("    ============================================================================\n");
		printf("    아무키나 누르세요"); rewind(stdin); getchar();
	}
}