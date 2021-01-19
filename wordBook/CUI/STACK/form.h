#ifndef _FORM_H
#define _FORM_H
typedef struct _wordBook WordBook;
void DisplayMenu();
void DisplayFindMenu();
void FindMenu(WordBook* wordBook);
void FormForRecording(WordBook* wordBook);
void FormForFindSpelling(WordBook* wordBook);
void FormForFindMeaning(WordBook* wordBook);
void FormForCorrecting(WordBook* wordBook);
void FormForErasing(WordBook* wordBook);
void FormForArranging(WordBook* wordBook);
void FormForShowAll(WordBook* wordBook);
#endif // !_FORM_H