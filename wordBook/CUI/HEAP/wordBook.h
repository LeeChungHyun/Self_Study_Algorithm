#ifndef _WORDBBOK_H
#define _WORDBOOK_H
typedef signed long int Long;

//단어에 대한 구조체
typedef struct _word{
	char spelling[64];
	char wordClass[11];
	char meaning[64];
	char example[128];
}Word;

//단어장에 대한 구조체
typedef struct _wordBook {
	Word (*words);
	Long capacity;
	Long length;
}WordBook;

void Create(WordBook* wordBook, Long capacity);
Long Record(WordBook* wordBook, char(*spelling), char(*wordClass), char(*meaning), char(*example));
void FindSpelling(WordBook* worBbook, char(*spelling), Long* (*indexes), Long* count);
void FindMeaning(WordBook* wordBook, char(*meaning), Long* (*indexes), Long* count);
Long Correct(WordBook* wordBook, Long index, char(*wordClass), char(*meaning), char(*example));
Long Erase(WordBook* wordBook, Long index);
void Arrange(WordBook* wordBook);
void Destroy(WordBook* wordBook);
Long Load(WordBook* wordBook);
Long Save(WordBook* wordBook);
#endif // !_WORDBBOK_H