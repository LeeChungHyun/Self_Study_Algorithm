#ifndef _WORDCARDHOLDER_H
#define _WORDCARDHOLDER_H
#include "LinkedList.h"

typedef signed long int Long;

typedef struct _word {
	char spelling[64];
	char wordClass[12];
	char meaning[64];
	char example[128];
}Word;

typedef struct _wordCard {
	Word word;
}WordCard;

typedef struct _wordCardHolder {
	LinkedList wordCards;
	Long length;
	WordCard* current;
}WordCardHolder;

void WordCardHolder_Create(WordCardHolder* wordCardHolder);
WordCard* PutIn(WordCardHolder* wordCardHolder, WordCard wordCard);
void FindSpelling(WordCardHolder* wordCardHolder, char(*spelling), WordCard** (*indexes), Long* count);
void FindMeaning(WordCardHolder* wordCardHolder, char(*meaning), WordCard** (*indexes), Long* count);
WordCard PutOut(WordCardHolder* wordCardHolder, WordCard* index);
WordCard* WordCardHolder_First(WordCardHolder* wordCardHolder);
WordCard* WordCardHolder_Next(WordCardHolder* wordCardHolder);
WordCard* WordCardHolder_Previous(WordCardHolder* wordCardHolder);
WordCard* WordCardHolder_Last(WordCardHolder* wordCardHolder);
WordCard* WordCardHolder_Move(WordCardHolder* wordCardHolder, WordCard* index);
void WordCardHolder_Destroy(WordCardHolder* wordCardHolder);
int CompareSpelings(void* one, void* other);
int CompareMeanings(void* one, void* other);
int CompareLinks(void* one, void* other);
Long Save(WordCardHolder* wordCardHolder);
Long Load(WordCardHolder* wordCardHolder);
Long KeepingCardLoad(WordCardHolder* wordCardHolder);
Long KeepingCardSave(WordCardHolder* wordCardHolder);
#endif // !_WORDCARDHOLDER_H
