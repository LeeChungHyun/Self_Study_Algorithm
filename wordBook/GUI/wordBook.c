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
	index = Record(&wordBook, "apple", "���", "���", "apple is a fruit");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].meaning, wordBook.words[index].example);
	index = Record(&wordBook, "ugly", "�����", "������", "he is ugly");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1,  wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].meaning, wordBook.words[index].example);
	index = Record(&wordBook, "pretty", "����", "�̻ڴ�", "she is pretty");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].meaning, wordBook.words[index].example);
	index = Record(&wordBook, "pretty", "�λ�", "��", "it's pretty cheap");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].meaning, wordBook.words[index].example);
	index = Record(&wordBook, "beautiful", "����", "�̻ڴ�", "she is so beautiful");
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
	FindMeaning(&wordBook, "�̻ڴ�", &indexes, &count);
	while (i < count) {
		printf("%d\t %s\t %s\t %s\t %s\n", indexes[i] + 1, wordBook.words[indexes[i]].meaning, wordBook.words[indexes[i]].wordClass, wordBook.words[indexes[i]].spelling, wordBook.words[indexes[i]].example);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}
	printf("-----------Correct----------\n");
	index = Correct(&wordBook, 1, "�����", "������", "your face is  ugly");
	printf("%d\t %s\t %s\t %s\t %s\n", index + 1, wordBook.words[index].spelling, wordBook.words[index].wordClass, wordBook.words[index].meaning, wordBook.words[index].example);

	printf("------------Erase-----------\n");
	index = Erase(&wordBook, 3);
	if (index == -1) {
		printf("���������ϴ�\n");
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
//�ܾ��� ����
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
//�ܾ��� ����
void Create(WordBook* wordBook, Long capacity) {
	wordBook->words = (Word(*))calloc(capacity, sizeof(Word));
	wordBook->capacity = capacity;
	wordBook->length = 0;
}
//�ܾ��� ����
void Destroy(WordBook* wordBook) {
	if (wordBook->words != NULL) {
		free(wordBook->words);
	}
}
//�ܾ��� ����
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
//�ܾ� ö�� ã��
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
//�ܾ� �ǹ� ã��
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
//�ܾ��� ��ġ��
Long Correct(WordBook* wordBook, Long index, char(*wordClass), char(*meaning), char(*example)) {
	strcpy(wordBook->words[index].wordClass, wordClass);
	strcpy(wordBook->words[index].meaning, meaning);
	strcpy(wordBook->words[index].example, example);
	return index;
}
//�ܾ��� �����
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
//�ܾ��� �����ϱ�
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
//�ܾ��� �����Ѵ�
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