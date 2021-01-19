#include "wordBook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
/*
int main(int argc, char* argv[]) {
	WordBook wordBook;
	Long index;
	Long(*indexes);
	Long count;
	Long i = 0;
	Create(&wordBook, 2);
	count = Load(&wordBook);

#if 0
	printf("-----------Record-----------\n");
	index = Record(&wordBook, "apple", "명사", "사과", "apple is a fruit");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].meaning, wordBook.words[index].example);
	index = Record(&wordBook, "ugly", "형용사", "못생긴", "he is ugly");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1,  wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].meaning, wordBook.words[index].example);
	index = Record(&wordBook, "pretty", "동사", "이쁘다", "she is pretty");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].meaning, wordBook.words[index].example);
	index = Record(&wordBook, "pretty", "부사", "꽤", "it's pretty cheap");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].meaning, wordBook.words[index].example);
	index = Record(&wordBook, "beautiful", "동사", "이쁘다", "she is so beautiful");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].meaning, wordBook.words[index].example);
	printf("------------FindSpelling------------\n");
	FindSpelling(&wordBook, "pretty", &indexes, &count);
	while (i < count) {
		printf("%d\t %s\t %s\t %s\t %s\n", indexes[i] + 1, wordBook.words[indexes[i]].spelling, wordBook.words[indexes[i]].wordClass, wordBook.words[indexes[i]].meaning, wordBook.words[indexes[i]].example);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}
	printf("------------FindMeaning------------\n");
	i = 0;
	FindMeaning(&wordBook, "이쁘다", &indexes, &count);
	while (i < count) {
		printf("%d\t %s\t %s\t %s\t %s\n", indexes[i] + 1, wordBook.words[indexes[i]].meaning, wordBook.words[indexes[i]].wordClass, wordBook.words[indexes[i]].spelling, wordBook.words[indexes[i]].example);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}
	printf("-----------Correct----------\n");
	index = Correct(&wordBook, 1, "형용사", "못생긴", "your face is  ugly");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].meaning, wordBook.words[index].example);

	printf("------------Erase-----------\n");
	index = Erase(&wordBook, 3);
	if (index == -1) {
		printf("지워졌습니다\n");
	}
	printf("-----------Arrange----------\n");
	Arrange(&wordBook);
	i = 0;
	while (i < wordBook.length) {
		printf("%d\t %s\t %s\t %s\t %s\n", i + 1, wordBook.words[i].spelling, wordBook.words[i].wordClass, wordBook.words[i].meaning, wordBook.words[i].example);
		i++;
	}
	Save(&wordBook);
#endif
	
	while (i < count) {
		printf("%d\t %s\t %s\t %s\t %s\n", i + 1, wordBook.words[i].spelling, wordBook.words[i].wordClass, wordBook.words[i].meaning, wordBook.words[i].example);
		i++;
	}
	
	Destroy(&wordBook);
	return 0;
}
*/
//단어장 적재
Long Load(WordBook* wordBook) {
	Word(*temp);
	Word word;
	FILE* file;
	Long i;
	Long j = 0;
	file = fopen("Words.dat", "rb");
	if (file != NULL) {
		fread(&word, sizeof(Word), 1, file);
		while (!feof(file)) {
			if (wordBook->length >= wordBook->capacity) {
				temp = (Word(*))calloc((wordBook->capacity) + 1, sizeof(Word));
				i = 0;
				while (i < wordBook->length) {
					temp[i] = wordBook->words[i];
					i++;
				}
				if (wordBook->words != NULL) {
					free(wordBook->words);
				}
				wordBook->words = temp;
				(wordBook->capacity)++;
			}
			wordBook->words[j] = word;
			j++;
			(wordBook->length)++;
			fread(&word, sizeof(Word), 1, file);
		}
		fclose(file);
	}
	return wordBook->length;
}
//단어장 생성
void Create(WordBook* wordBook, Long capacity) {
	wordBook->words = (Word(*))calloc(capacity, sizeof(Word));
	wordBook->capacity = capacity;
	wordBook->length = 0;
}
//단어장 해제
void Destroy(WordBook* wordBook) {
	if (wordBook->words != NULL) {
		free(wordBook->words);
	}
}
//단어장 기재
Long Record(WordBook* wordBook, char(*spelling), char(*wordClass), char(*meaning), char(*example)) {
	Word(*temp);
	Long index;
	Long i = 0;

	if (wordBook->length >= wordBook->capacity) {
		temp = (Word(*))calloc((wordBook->capacity) + 1, sizeof(Word));
		while (i < wordBook->length) {
			temp[i] = wordBook->words[i];
			i++;
		}

		if (wordBook->words != NULL) {
			free(wordBook->words);
		}

		wordBook->words = temp;
		(wordBook->capacity)++;
	}
	index = wordBook->length;
	strcpy(wordBook->words[index].spelling, spelling);
	strcpy(wordBook->words[index].wordClass, wordClass);
	strcpy(wordBook->words[index].meaning, meaning);
	strcpy(wordBook->words[index].example, example);
	(wordBook->length)++;
	return index;
}
//단어 철자 찾기
void FindSpelling(WordBook* wordBook, char(*spelling), Long* (*indexes), Long* count) {
	Long i = 0;
	Long index = 0;
	*count = 0;
	*indexes = (Long(*))calloc(wordBook->length, sizeof(Long));
	while (index < wordBook->length) {
		if (strcmp(wordBook->words[index].spelling, spelling) == 0) {
			(*indexes)[i] = index;
			i++;
			(*count)++;
		}
		index++;
	}
}
//단어 의미 찾기
void FindMeaning(WordBook* wordBook, char(*meaning), Long* (*indexes), Long* count) {
	Long i = 0;
	Long index = 0;
	*count = 0;
	*indexes = (Long(*))calloc(wordBook->length, sizeof(Long));
	while (index < wordBook->length) {
		if (strcmp(wordBook->words[index].meaning, meaning) == 0) {
			(*indexes)[i] = index;
			i++;
			(*count)++;
		}
		index++;
	}
}
//단어장 고치기
Long Correct(WordBook* wordBook, Long index, char(*wordClass), char(*meaning), char(*example)) {
	strcpy(wordBook->words[index].wordClass, wordClass);
	strcpy(wordBook->words[index].meaning, meaning);
	strcpy(wordBook->words[index].example, example);
	return index;
}
//단어장 지우기
Long Erase(WordBook* wordBook, Long index) {
	Word(*temp) = NULL;
	Long i = 0;
	Long j = 0;

	if (wordBook->capacity > 1) {
		temp = (Word(*))calloc((wordBook->capacity) - 1, sizeof(Word));
	}
	while (i < index) {
		temp[j] = wordBook->words[i];
		j++;
		i++;
	}
	i = index + 1;

	while (i < wordBook->length) {
		temp[j] = wordBook->words[i];
		j++;
		i++;
	}
	if (wordBook->words != NULL) {
		free(wordBook->words);
		wordBook->words = NULL;
	}
	if (wordBook->capacity > 1) {
		wordBook->words = temp;
	}
	(wordBook->length)--;
	(wordBook->capacity)--;
	index = -1;
	return index;
}
//단어장 정리하기
void Arrange(WordBook* wordBook) {
	Word temp;
	Long i = 0;
	Long j;
	while (i < wordBook->length) {
		j = 0;
		while (j < (wordBook->length)-i-1) {
			if (strcmp(wordBook->words[j].spelling, wordBook->words[j+1].spelling) > 0) {
				temp = wordBook->words[j];
				wordBook->words[j] = wordBook->words[j+1];
				wordBook->words[j+1] = temp;
			}
			j++;
		}
		i++;
	}
}
//단어장 저장한다
Long Save(WordBook* wordBook) {
	Long i = 0;
	FILE* file = fopen("Words.dat", "wb");
	if (file != NULL) {
		while (i < wordBook->length) {
			fwrite(wordBook->words + i, sizeof(Word), 1, file);
			i++;
		}
		fclose(file);
	}
	return wordBook->length;
}