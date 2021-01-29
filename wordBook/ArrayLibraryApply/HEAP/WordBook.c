#include "WordBook.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

/*
int main(int argc, char* argv[]) {
	WordBook wordBook;
	Word word;
	Long index;
	Long i;
	Long(*indexes);
	Long count;

	//����
	WordBook_Create(&wordBook, 3);

	
	count = Load(&wordBook);
	i = 0;
	while (i < count) {
		word = WordBook_GetAt(&wordBook, i);
		printf("%s\t%s\t%s\t%s\n", word.spelling, word.wordClass, word.meaning, word.example);
		i++;
	}
	printf("\n");
	
#if 0
	//����
	index = Record(&wordBook, "apple", "���", "���", "apple is an fruit");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s\t%s\t%s\t%s\n", word.spelling, word.wordClass, word.meaning, word.example);

	index = Record(&wordBook, "pretty", "����", "�̻ڴ�", "she is pretty");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s\t%s\t%s\t%s\n", word.spelling, word.wordClass, word.meaning, word.example);

	index = Record(&wordBook, "pretty", "�λ�", "��", "it is pretty cheap");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s\t%s\t%s\t%s\n", word.spelling, word.wordClass, word.meaning, word.example);

	index = Record(&wordBook, "beautiful", "����", "�̻ڴ�", "she is beautiful");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s\t%s\t%s\t%s\n", word.spelling, word.wordClass, word.meaning, word.example);
	printf("\n");
	//ö�� ã��
	FindSpelling(&wordBook, "pretty", &indexes, &count);
	i = 0;
	while (i < count) {
		index = indexes[i];
		word = WordBook_GetAt(&wordBook, index);
		printf("%s\t%s\t%s\t%s\n", word.spelling, word.wordClass, word.meaning, word.example);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}
	printf("\n");
	//�ǹ�ã��
	FindMeaning(&wordBook, "�̻ڴ�", &indexes, &count);
	i = 0;
	while (i < count) {
		index = indexes[i];
		word = WordBook_GetAt(&wordBook, index);
		printf("%s\t%s\t%s\t%s\n", word.spelling, word.wordClass, word.meaning, word.example);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}
	printf("\n");

	//��ġ��
	index = Correct(&wordBook, 0, "���", "���", "my favorite fruit is apple");
	word = WordBook_GetAt(&wordBook, index);
	printf("%s\t%s\t%s\t%s\n", word.spelling, word.wordClass, word.meaning, word.example);
	printf("\n");

	//�����
	index = Erase(&wordBook, 1);
	if (index == -1){
		printf("��������\n");
	}
	printf("\n");

	//�����ϱ�
	Arrange(&wordBook);
	i = 0;
	while (i < wordBook.length) {
		word = WordBook_GetAt(&wordBook, i);
		printf("%s\t%s\t%s\t%s\n", word.spelling, word.wordClass, word.meaning, word.example);
		i++;
	}
	printf("\n");

	//�����ϱ�
	Save(&wordBook);
#endif

	//�����ϱ�
	WordBook_Destroy(&wordBook);
	
	return 0;
}
*/

Long Load(WordBook* wordBook) {
	Word word;
	size_t temp;

	FILE* file = fopen("WordBook.dat", "rb");
	if (file != NULL) {
		temp = fread(&word, sizeof(Word), 1, file);
		while (!feof(file) && temp != 0) {
			if (wordBook->length < wordBook->capacity) {
				Store(&wordBook->words, wordBook->length, &word, sizeof(Word));
			}
			else {
				AppendFromRear(&wordBook->words, &word, sizeof(Word));
				wordBook->capacity++;
			}
			wordBook->length++;
			temp = fread(&word, sizeof(Word), 1, file);
		}
		fclose(file);
	}
	return wordBook->length;
}
void WordBook_Create(WordBook* wordBook, Long capacity) {
	Create(&wordBook->words, capacity, sizeof(Word));
	wordBook->capacity = capacity;
	wordBook->length = 0;
}

Long Record(WordBook* wordBook, char(*spelling), char(*wordClass), char(*meaning), char(*example)) {
	Word word;
	Long index;

	strcpy(word.spelling, spelling);
	strcpy(word.wordClass, wordClass);
	strcpy(word.meaning, meaning);
	strcpy(word.example, example);
	if (wordBook->capacity > wordBook->length) {
		index = Store(&wordBook->words, wordBook->length, &word, sizeof(Word));
	}
	else {
		index = AppendFromRear(&wordBook->words, &word, sizeof(Word));
		(wordBook->capacity)++;
	}
	(wordBook->length)++;
	return index;
}

void FindSpelling(WordBook* wordBook, char(*spelling), Long* (*indexes), Long* count) {
	LinearSearchDuplicate(&wordBook->words, spelling, indexes, count, sizeof(Word), CompareSpellings);
}

void FindMeaning(WordBook* wordBook, char(*meaning), Long* (*indexes), Long* count) {
	LinearSearchDuplicate(&wordBook->words, meaning, indexes, count, sizeof(Word), CompareMeanings);
}

Long Correct(WordBook* wordBook, Long index, char(*wordClass), char(*meaning), char(*example)) {
	Word word;
	GetAt(&wordBook->words, index, &word, sizeof(Word));
	strcpy(word.wordClass, wordClass);
	strcpy(word.meaning, meaning);
	strcpy(word.example, example);
	index = Modify(&wordBook->words, index, &word, sizeof(Word));
	return index;
}

Long Erase(WordBook* wordBook, Long index) {
	index = Delete(&wordBook->words, index, sizeof(Word));
	(wordBook->capacity)--;
	(wordBook->length)--;
	return index;
}

void Arrange(WordBook* wordBook) {
	BubbleSort(&wordBook->words, sizeof(Word), CompareWords);
}

Word WordBook_GetAt(WordBook* wordBook, Long index) {
	Word word;
	GetAt(&wordBook->words, index, &word, sizeof(Word));
	return word;
}

void WordBook_Destroy(WordBook* wordBook) {
	Destroy(&wordBook->words);
}

Long Save(WordBook* wordBook) {
	Word word;
	Long i;

	FILE* file = fopen("WordBook.dat", "wb");
	if (file != NULL) {
		i = 0;
		while (i < wordBook->length) {
			GetAt(&wordBook->words, i, &word, sizeof(Word));
			fwrite(&word, sizeof(Word), 1, file);
			i++;
		}
		fclose(file);
	}
	return wordBook->length;
}

int CompareSpellings(void* one, void* other) {
	Word* one_ = (Word*)one;
	char(*other_) = (char*)other;
	return strcmp(one_->spelling, other_);
}

int CompareMeanings(void* one, void* other) {
	Word* one_ = (Word*)one;
	char(*other_) = (char*)other;
	return strcmp(one_->meaning, other_);
}

int CompareWords(void* one, void* other) {
	Word* one_ = (Word*)one;
	Word* other_ = (Word*)other;
	return strcmp(one_->spelling, other_->spelling);
}