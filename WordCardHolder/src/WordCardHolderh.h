#ifndef _WORDCARDHOLDER_H
#define _WORDCARDHOLDER_H
typedef signed long int Long;

typedef struct _word {
	char spelling[64];
	char wordClass[11];
	char meaning[64];
	char example[128];
}Word;

typedef struct _wordCard WordCard;//전방 선언

typedef struct _wordCard {
	Word word;
	WordCard* next;
}WordCard;

typedef struct _wordCardHolder {
	WordCard* first;
	WordCard* current;
	Long length;
}WordCardHolder;

void Create(WordCardHolder* wordCardHolder);
WordCard* PutIn(WordCardHolder* wordCardHolder, WordCard wordCard);
WordCard PutOut(WordCardHolder* wordCardHolder, WordCard* index);
void FindSpelling(WordCardHolder* wordCardHolder, char(*spelling), WordCard** (*indexes), Long* count);
void FindMeaning(WordCardHolder* wordCardHolder, char(*meaning), WordCard** (*indexes), Long* count);
WordCard* First(WordCardHolder* wordCardHolder);
WordCard* Next(WordCardHolder* wordCardHolder);
WordCard* Previous(WordCardHolder* wordCardHolder);
WordCard* Last(WordCardHolder* wordCardHolder); 
WordCard* Move(WordCardHolder* wordCardHolder, WordCard* index);
void Arrange(WordCardHolder* wordCardHolder);
void Destroy(WordCardHolder* wordCardHolder);
Long Load(WordCardHolder* wordCardHolder);
Long KeepingCardLoad(WordCardHolder* wordCardHolder);
Long Save(WordCardHolder* wordCardHolder);
Long KeepingCardSave(WordCardHolder* wordCardHolder);
#endif // !_WORDCARDHOLDER_H