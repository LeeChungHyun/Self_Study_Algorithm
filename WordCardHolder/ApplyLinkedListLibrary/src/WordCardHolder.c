#include "WordCardHolder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

void WordCardHolder_Create(WordCardHolder* wordCardHolder) {
	Create(&wordCardHolder->wordCards);
	wordCardHolder->length = 0;
	wordCardHolder->current = NULL;
}

WordCard* PutIn(WordCardHolder* wordCardHolder, WordCard wordCard) {
	Node* node;
	node = AppendFromTail(&wordCardHolder->wordCards, &wordCard, sizeof(WordCard));
	(wordCardHolder->length)++;
	wordCardHolder->current = (WordCard*)(node + 1);
	return wordCardHolder->current;
}

void FindSpelling(WordCardHolder* wordCardHolder, char(*spelling), WordCard** (*indexes), Long* count) {
	Node* (*nodes);
	Long i = 0;
	*indexes = (WordCard * (*))calloc(wordCardHolder->length, sizeof(WordCard*));
	LinearSearchDuplicate(&wordCardHolder->wordCards, spelling, &nodes, count, CompareSpelings);
	while (i < *count) {
		(*indexes)[i] = (WordCard*)(nodes[i] + 1);
		i++;
	}
	if (nodes != NULL) {
		free(nodes);
	}
}

void FindMeaning(WordCardHolder* wordCardHolder, char(*meaning), WordCard** (*indexes), Long* count) {
	Long i = 0;
	Node* (*nodes);
	LinearSearchDuplicate(&wordCardHolder->wordCards, meaning, &nodes, count, CompareMeanings);
	*indexes = (WordCard * (*))calloc(wordCardHolder->length, sizeof(WordCard*));
	while (i < *count) {
		(*indexes)[i] = (WordCard*)(nodes[i] + 1);
		i++;
	}
	if (nodes != NULL) {
		free(nodes);
	}
}

WordCard PutOut(WordCardHolder* wordCardHolder, WordCard* index) {
	Node* node;
	WordCard wordCard;
	node = LinearSearchUnique(&wordCardHolder->wordCards, index, CompareLinks);
	GetAt(&wordCardHolder->wordCards, node, &wordCard, sizeof(WordCard));
	node = Delete(&wordCardHolder->wordCards, node);
	(wordCardHolder->length)--;
	if (wordCardHolder->wordCards.current != NULL) {
		wordCardHolder->current = (WordCard*)(wordCardHolder->wordCards.current + 1);
	}
	return wordCard;
}

WordCard* WordCardHolder_First(WordCardHolder* wordCardHolder) {
	Node* node;
	node = First(&wordCardHolder->wordCards);
	wordCardHolder->current = (WordCard*)(node + 1);
	return wordCardHolder->current;
}

WordCard* WordCardHolder_Next(WordCardHolder* wordCardHolder) {
	Node* node;
	node = Next(&wordCardHolder->wordCards);
	wordCardHolder->current = (WordCard*)(node + 1);
	return wordCardHolder->current;
}

WordCard* WordCardHolder_Previous(WordCardHolder* wordCardHolder) {
	Node* node;
	node = Previous(&wordCardHolder->wordCards);
	wordCardHolder->current = (WordCard*)(node + 1);
	return wordCardHolder->current;
}

WordCard* WordCardHolder_Last(WordCardHolder* wordCardHolder) {
	Node* node;
	node = Last(&wordCardHolder->wordCards);
	wordCardHolder->current = (WordCard*)(node + 1);
	return wordCardHolder->current;
}

WordCard* WordCardHolder_Move(WordCardHolder* wordCardHolder, WordCard* index) {
	Node* node;
	node = LinearSearchUnique(&wordCardHolder->wordCards, index, CompareLinks);
	node = Move(&wordCardHolder->wordCards, node);
	wordCardHolder->current = (WordCard*)(node + 1);
	return wordCardHolder->current;
}

Long Save(WordCardHolder* wordCardHolder) {
	WordCard wordCard;
	Word word;
	Long count = 0;
	Long i = 0;
	Node* node;
	Node* previous = NULL;
	FILE* file = fopen("Words.dat", "wb");

	if (file != NULL) {
		node = First(&wordCardHolder->wordCards);
		while (node != previous) {
			GetAt(&wordCardHolder->wordCards, node, &wordCard, sizeof(WordCard));
			fwrite(&wordCard.word, sizeof(Word), 1, file);
			count++;
			previous = node;
			node = Next(&wordCardHolder->wordCards);
		}
		fclose(file);
	}
	return count;
}

Long KeepingCardSave(WordCardHolder* wordCardHolder) {
	WordCard wordCard;
	Word word;
	Long count = 0;
	Long i = 0;
	Node* node;
	Node* previous = NULL;
	FILE* file = fopen("KeepingWords.dat", "wb");

	if (file != NULL) {
		node = First(&wordCardHolder->wordCards);
		while (node != previous) {
			GetAt(&wordCardHolder->wordCards, node, &wordCard, sizeof(WordCard));
			fwrite(&wordCard.word, sizeof(Word), 1, file);
			count++;
			previous = node;
			node = Next(&wordCardHolder->wordCards);
		}
		fclose(file);
	}
	return count;
}

Long Load(WordCardHolder* wordCardHolder) {
	FILE* file = fopen("Words.dat", "rb");
	WordCard wordCard;
	WordCard* previous = NULL;
	Word word;
	Node* node;

	if (file != NULL) {
		fread(&word, sizeof(Word), 1, file);
		while (!feof(file)) {
			wordCard.word = word;
			node = AppendFromTail(&wordCardHolder->wordCards, &wordCard, sizeof(WordCard));
			(wordCardHolder->length)++;
			wordCardHolder->current = (WordCard*)(node + 1);
			fread(&word, sizeof(Word), 1, file);
		}
		fclose(file);
	}
	return wordCardHolder->length;
}

Long KeepingCardLoad(WordCardHolder* wordCardHolder) {
	FILE* file = fopen("KeepingWords.dat", "rb");
	WordCard wordCard;
	WordCard* previous = NULL;
	Word word;
	Node* node;

	if (file != NULL) {
		fread(&word, sizeof(Word), 1, file);
		while (!feof(file)) {
			wordCard.word = word;
			node = AppendFromTail(&wordCardHolder->wordCards, &wordCard, sizeof(WordCard));
			(wordCardHolder->length)++;
			wordCardHolder->current = (WordCard*)(node + 1);
			fread(&word, sizeof(Word), 1, file);
		}
		fclose(file);
	}
	return wordCardHolder->length;
}

void WordCardHolder_Destroy(WordCardHolder* wordCardHolder) {
	Destroy(&wordCardHolder->wordCards);
}

int CompareSpelings(void* one, void* other) {
	WordCard* one_ = (WordCard*)one;
	char* other_ = (char*)other;
	return strcmp(one_->word.spelling, other_);
}

int CompareMeanings(void* one, void* other) {
	WordCard* one_ = (WordCard*)one;
	char* other_ = (char*)other;
	return strcmp(one_->word.meaning, other_);
}

int CompareLinks(void* one, void* other) {
	WordCard* one_ = one;
	WordCard* other_ = other;
	int ret;
	if (one_ > other_) { ret = 1; }
	else if (one_ == other_) { ret = 0; }
	else if (one_ < other_) { ret = -1; }
	return ret;
}

/*
int main(int argc, char* argv[]) {
	WordCardHolder wordCardHolder;
	WordCard wordCard;
	WordCard* index;
	WordCard* (*indexes);
	Long i;
	Long count;

	WordCard wordCard1 = { "apple", "명사", "사과","apple is a fruit"};
	WordCard wordCard2 = { "pretty", "동사", "이쁘다","she is pretty"};
	WordCard wordCard3 = {"pretty", "부사", "꽤","it is pretty cheap"};
	WordCard wordCard4 = {"beautiful", "동사", "이쁘다","she is beautiful"};

	WordCardHolder_Create(&wordCardHolder);
	printf("<불러오기>\n");
	Load(&wordCardHolder);
	printf("%s\t%s\t%s\t%s\n", wordCardHolder.current->word.spelling, wordCardHolder.current->word.wordClass, wordCardHolder.current->word.meaning, wordCardHolder.current->word.example);
	
	printf("<꽂기>\n");
	index = PutIn(&wordCardHolder, wordCard1);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	index = PutIn(&wordCardHolder, wordCard2);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	index = PutIn(&wordCardHolder, wordCard3);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	index = PutIn(&wordCardHolder, wordCard4);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	printf("<첫번째 단어 카드 찾기>\n");
	index = WordCardHolder_First(&wordCardHolder);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	printf("<다음 카드 찾기>\n");
	index = WordCardHolder_Next(&wordCardHolder);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	printf("<이전 카드 찾기>\n");
	index = WordCardHolder_Previous(&wordCardHolder);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	printf("<마지막 카드 찾기>\n");
	index = WordCardHolder_Last(&wordCardHolder);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	printf("<맨 처음 단어카드 이동>\n");
	index = WordCardHolder_First(&wordCardHolder);
	index = WordCardHolder_Move(&wordCardHolder, index);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	printf("<해당 단어카드 꺼내기>\n");
	wordCard = PutOut(&wordCardHolder, index);
	printf("%s\t%s\t%s\t%s\n", wordCard.word.spelling, wordCard.word.wordClass, wordCard.word.meaning, wordCard.word.example);

	printf("<철자찾기>\n");
	FindSpelling(&wordCardHolder, "pretty", &indexes, &count);
	i = 0;
	while (i < count) {
		index = indexes[i];
		printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}
	printf("\n");

	printf("<의미찾기>\n");
	FindMeaning(&wordCardHolder, "이쁘다", &indexes, &count);
	i = 0;
	while (i < count) {
		index = indexes[i];
		printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}
	printf("\n");
	
	Save(&wordCardHolder);
	printf("<저장햇음>\n");

	Destroy(&wordCardHolder);
	printf("<삭제햇음>\n");
	
	return 0;
}
*/