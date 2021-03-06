#include "WordCardHolderh.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

#if 0
int main(int argc, char* argv[]) {
	WordCardHolder wordCardHolder;
	WordCard wordCard1 = { {"apple", "명사", "사과","apple is a fruit"}, NULL };
	WordCard wordCard2 = { {"pretty", "동사", "이쁘다","she is pretty"}, NULL };
	WordCard wordCard3 = { {"pretty", "부사", "꽤","it is pretty cheap"}, NULL };
	WordCard wordCard4 = { {"beautiful", "동사", "이쁘다","she is beautiful"},  NULL };

	WordCard wordCard;
	WordCard* index;
	WordCard* (*indexes);
	WordCard* temp = NULL;
	Long count;
	Long i;

	Create(&wordCardHolder);

	printf("<꽂기>\n");
	index = PutIn(&wordCardHolder, wordCard1);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	index = PutIn(&wordCardHolder, wordCard2);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	index = PutIn(&wordCardHolder, wordCard3);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	index = PutIn(&wordCardHolder, wordCard4);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	printf("<첫번째 명함 찾기>\n");
	index = First(&wordCardHolder);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	printf("<다음 명함 찾기>\n");
	index = Next(&wordCardHolder);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	printf("<이전 명함 찾기>\n");
	index = Previous(&wordCardHolder);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	printf("<마지막 명함 찾기>\n");
	index = Last(&wordCardHolder);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

	printf("<명함 꺼내기>\n");
	wordCard = PutOut(&wordCardHolder, index);
	printf("%s\t%s\t%s\t%s\n", wordCard.word.spelling, wordCard.word.wordClass, wordCard.word.meaning, wordCard.word.example);

	printf("<명함 다시 꽂기>\n");
	index = PutIn(&wordCardHolder, wordCard);
	printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);

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

	printf("<정리하기>\n");
	Arrange(&wordCardHolder);
	index = First(&wordCardHolder);
	while (index != temp) {
		printf("%s\t%s\t%s\t%s\n", index->word.spelling, index->word.wordClass, index->word.meaning, index->word.example);
		temp = index;
		index = Next(&wordCardHolder);
	}

	//지우기
	Destroy(&wordCardHolder);

	return 0;
}
#endif

void Create(WordCardHolder* wordCardHolder) {
	wordCardHolder->first = NULL;
	wordCardHolder->length = 0;
	wordCardHolder->current = NULL;
}

WordCard* PutIn(WordCardHolder* wordCardHolder, WordCard wordCard) {
	WordCard* previous = NULL;

	wordCardHolder->current = wordCardHolder->first;
	while (wordCardHolder->current != NULL) {
		previous = wordCardHolder->current;
		wordCardHolder->current = wordCardHolder->current->next;
	}
	wordCardHolder->current = (WordCard*)malloc(sizeof(WordCard));
	(*wordCardHolder->current) = wordCard;
	if (previous != NULL) {
		previous->next = wordCardHolder->current;
	}
	else {
		wordCardHolder->first = wordCardHolder->current;
	}
	(wordCardHolder->length)++;

	return wordCardHolder->current;
}

WordCard PutOut(WordCardHolder* wordCardHolder, WordCard* index) {
	WordCard* previous = NULL;
	WordCard wordCard;

	wordCardHolder->current = wordCardHolder->first;
	while (wordCardHolder->current != index) {
		previous = wordCardHolder->current;
		wordCardHolder->current = wordCardHolder->current->next;
	}
	if (previous != NULL) {
		previous->next = index->next;
	}
	else {
		wordCardHolder->first = index->next;
	}
	if (index->next != NULL) {
		wordCardHolder->current = index->next;
	}
	else {
		wordCardHolder->current = previous;
	}
	wordCard = *index;
	wordCard.next = NULL;
	if (index != NULL) {
		free(index);
	}
	(wordCardHolder->length)--;
	return wordCard;
}

void FindSpelling(WordCardHolder* wordCardHolder, char(*spelling), WordCard** (*indexes), Long* count) {
	Long i = 0;
	*count = 0;

	*indexes = (WordCard * (*))calloc(wordCardHolder->length, sizeof(WordCard*));
	wordCardHolder->current = wordCardHolder->first;

	while (wordCardHolder->current != NULL) {
		if (strcmp(wordCardHolder->current->word.spelling, spelling) == 0) {
			(*indexes)[i] = wordCardHolder->current;
			i++;
			(*count)++;
		}
		wordCardHolder->current = wordCardHolder->current->next;
	}
}

void FindMeaning(WordCardHolder* wordCardHolder, char(*meaning), WordCard** (*indexes), Long* count) {
	Long i = 0;
	*count = 0;

	*indexes = (WordCard * (*))calloc(wordCardHolder->length, sizeof(WordCard*));
	wordCardHolder->current = wordCardHolder->first;

	while (wordCardHolder->current != NULL) {
		if (strcmp(wordCardHolder->current->word.meaning, meaning) == 0) {
			(*indexes)[i] = wordCardHolder->current;
			i++;
			(*count)++;
		}
		wordCardHolder->current = wordCardHolder->current->next;
	}
}

WordCard* First(WordCardHolder* wordCardHolder) {
	wordCardHolder->current = wordCardHolder->first;
	return wordCardHolder->current;
}

WordCard* Next(WordCardHolder* wordCardHolder) {
	WordCard* previous = wordCardHolder->current;
	wordCardHolder->current = wordCardHolder->current->next;
	if (wordCardHolder->current == NULL) {
		wordCardHolder->current = previous;
	}
	return wordCardHolder->current;
}

WordCard* Previous(WordCardHolder* wordCardHolder) {
	WordCard* previous = NULL;
	WordCard* current = wordCardHolder->current;

	wordCardHolder->current = wordCardHolder->first;
	while (wordCardHolder->current != current) {
		previous = wordCardHolder->current;
		wordCardHolder->current = wordCardHolder->current->next;
	}
	if (previous != NULL) {
		wordCardHolder->current = previous;
	}
	return wordCardHolder->current;
}

WordCard* Last(WordCardHolder* wordCardHolder) {
	WordCard* previous = NULL;
	while (wordCardHolder->current != NULL) {
		previous = wordCardHolder->current;
		wordCardHolder->current = wordCardHolder->current->next;
	}
	if (previous != NULL) {
		wordCardHolder->current = previous;
	}
	return wordCardHolder->current;
}

WordCard* Move(WordCardHolder* wordCardHolder, WordCard* index) {
	wordCardHolder->current = index;
	return wordCardHolder->current;
}

void Arrange(WordCardHolder* wordCardHolder) {
	WordCard* previous;
	WordCard* temp;
	WordCard* next;
	Long i = 1;
	Long j;
	while (i < wordCardHolder->length) {
		previous = NULL;
		wordCardHolder->current = wordCardHolder->first;
		next = wordCardHolder->current->next;
		j = 1;
		while (j <= wordCardHolder->length - i) {
			if (strcmp(wordCardHolder->current->word.spelling, next->word.spelling) > 0) {
				if (previous != NULL) {
					temp = previous->next;
					previous->next = wordCardHolder->current->next;
				}
				else {
					temp = wordCardHolder->first;
					wordCardHolder->first = wordCardHolder->current->next;
				}
				wordCardHolder->current->next = next->next;
				next->next = temp;
				previous = next;
			}
			else {
				previous = wordCardHolder->current;
				wordCardHolder->current = next;
			}
			next = wordCardHolder->current->next;
			j++;
		}
		i++;
	}
}

void Destroy(WordCardHolder* wordCardHolder) {
	wordCardHolder->current = wordCardHolder->first;
	while (wordCardHolder->current != NULL) {
		wordCardHolder->first = wordCardHolder->current->next;
		wordCardHolder->current = NULL;
		wordCardHolder->current = wordCardHolder->first;
	}
}

Long Load(WordCardHolder* wordCardHolder) {
	FILE* file = fopen("Words.dat", "rb");
	WordCard wordCard;
	WordCard* previous = NULL;
	Word word;
	Long index;

	if (file != NULL) {
		fread(&word, sizeof(Word), 1, file);
		while (!feof(file)) {
			wordCard.word = word;
			wordCard.next = NULL;
			wordCardHolder->current = (WordCard*)malloc(sizeof(WordCard));
			*(wordCardHolder->current) = wordCard;
			if (previous != NULL) {
				previous->next = wordCardHolder->current;
			}
			else {
				wordCardHolder->first = wordCardHolder->current;
			}
			previous = wordCardHolder->current;
			(wordCardHolder->length)++;
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
	Long index;

	if (file != NULL) {
		fread(&word, sizeof(Word), 1, file);
		while (!feof(file)) {
			wordCard.word = word;
			wordCard.next = NULL;
			wordCardHolder->current = (WordCard*)malloc(sizeof(WordCard));
			*(wordCardHolder->current) = wordCard;
			if (previous != NULL) {
				previous->next = wordCardHolder->current;
			}
			else {
				wordCardHolder->first = wordCardHolder->current;
			}
			previous = wordCardHolder->current;
			(wordCardHolder->length)++;
			fread(&word, sizeof(Word), 1, file);
		}
		fclose(file);
	}
	return wordCardHolder->length;
}

Long Save(WordCardHolder* wordCardHolder) {
	Word word;
	Long count = 0;
	Long i = 0;
	FILE* file = fopen("Words.dat", "wb");
	if (file != NULL) {
		wordCardHolder->current = wordCardHolder->first;
		//단어첩의 끝이 아닌동안 반복한다
		while (wordCardHolder->current != NULL) {
			fwrite(&wordCardHolder->current->word + i, sizeof(Word), 1, file);
			count++;
			wordCardHolder->current = wordCardHolder->current->next;
		}
		fclose(file);
	}
	return count;
}

Long KeepingCardSave(WordCardHolder* wordCardHolder) {
	Word word;
	Long count = 0;
	Long i = 0;
	FILE* file = fopen("KeepingWords.dat", "wb");
	if (file != NULL) {
		wordCardHolder->current = wordCardHolder->first;
		//단어첩의 끝이 아닌동안 반복한다
		while (wordCardHolder->current != NULL) {
			fwrite(&wordCardHolder->current->word + i, sizeof(Word), 1, file);
			count++;
			wordCardHolder->current = wordCardHolder->current->next;
		}
		fclose(file);
	}
	return count;
}
