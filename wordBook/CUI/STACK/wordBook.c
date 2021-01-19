#include "wordBook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

//단어장 적재
Long Load(WordBook* wordBook) {
	Word word;
	Long i = 0;
	FILE* file = fopen("Words.dat", "rb");
	if (file != NULL) {
		fread(&word, sizeof(Word), 1, file);
		while (!feof(file)) {
			wordBook->words[i] = word;
			i++;
			(wordBook->length)++;
			fread(&word, sizeof(Word), 1, file);
		}
		fclose(file);
	}
	return wordBook->length;
}
//단어장 기재
Long Record(WordBook* wordBook, char(*spelling), char(*wordClass), char(*meaning), char(*example)) {
	Long i = 0;
	Long index = -1;
	while (i < wordBook->capacity && strcmp(wordBook->words[i].spelling, "")!=0) {
		i++;
	}
	if (i < wordBook->capacity) {
		index = i;
		strcpy(wordBook->words[index].spelling, spelling);
		strcpy(wordBook->words[index].wordClass, wordClass);
		strcpy(wordBook->words[index].meaning, meaning);
		strcpy(wordBook->words[index].example, example);
		(wordBook->length)++;
	}
	return index;
}
//단어 철자 찾기
void FindSpelling(WordBook* wordBook, char(*spelling), Long(*indexes), Long* count) {
	Long i = 0;
	Long index = 0;
	*count = 0;
	while (index < wordBook->length) {
		if (strcmp(wordBook->words[index].spelling, spelling) == 0) {
			indexes[i] = index;
			i++;
			(*count)++;
		}
		index++;
	}
}
//단어 의미 찾기
void FindMeaning(WordBook* wordBook, char(*meaning), Long(*indexes), Long* count) {
	Long i = 0;
	Long index = 0;
	*count = 0;
	while (index < wordBook->length) {
		if (strcmp(wordBook->words[index].meaning, meaning) == 0) {
			indexes[i] = index;
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
	strcpy(wordBook->words[index].spelling, "X");
	index = -1;
	return index;
}
//단어장 정리하기
void Arrange(WordBook* wordBook) {
	Word temp;
	Long i = 0;
	Long j;
	Long k = 1;
	Long count = 0;
	while (i < wordBook->length) {
		j = i + 1;
		while (j < wordBook->length) {
			if (strcmp(wordBook->words[i].spelling, wordBook->words[j].spelling) < 0) {
				temp = wordBook->words[i];
				wordBook->words[i] = wordBook->words[j];
				wordBook->words[j] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < wordBook->length && strcmp(wordBook->words[i].spelling, "X") != 0) {
		count++;
		i++;
	}
	while (k < count) {
		temp = wordBook->words[k];
		j = k - 1;
		while (j >= 0 && strcmp(wordBook->words[j].spelling, temp.spelling) > 0) {
			wordBook->words[j + 1] = wordBook->words[j];
			j--;
		}
		wordBook->words[j + 1] = temp;
		k++;
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