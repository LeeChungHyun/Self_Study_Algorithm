#ifndef _WORDBOOK_H
#define _WORDBOOK_H
#include "Array.h"

typedef signed long int Long;

typedef struct _word {
	char spelling[64];
	char wordClass[12];
	char meaning[64];
	char example[128];
}Word;

typedef struct _wordBook {
	Array words;
	Long capacity;
	Long length;
}WordBook;

void WordBook_Create(WordBook* wordBook, Long capacity);
Long Record(WordBook* wordBook, char(*spelling), char(*wordClass), char(*meaning), char(*example));
void FindSpelling(WordBook* wordBook, char(*spelling), Long* (*indexes), Long* count);
void FindMeaning(WordBook* wordBook, char(*meaning), Long* (*indexes), Long* count);
Long Correct(WordBook* wordBook, Long index, char(*wordClass), char(*meaning), char(*example));
Long Erase(WordBook* wordBook, Long index);
void Arrange(WordBook* wordBook);
Word WordBook_GetAt(WordBook* wordBook, Long index);
void WordBook_Destroy(WordBook* wordBook);
int CompareSpellings(void* one, void* other);
int CompareMeanings(void* one, void* other);
int CompareWords(void* one, void* other);
Long Load(WordBook* wordBook);
Long Save(WordBook* wordBook);
#endif // !_WORDBOOK_H
