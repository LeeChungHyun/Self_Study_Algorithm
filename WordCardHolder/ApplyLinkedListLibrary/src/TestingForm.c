#include "TestingForm.h"
#include "WordCardHolder.h"
#include "resource.h"
#include <CommCtrl.h>
#include <stdlib.h>
#include <WinUser.h>

BOOL CALLBACK TestingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (message) {
	case WM_INITDIALOG: ret = TestingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = TestingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = TestingForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL TestingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_FIRST: ret = TestingForm_OnFirstButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_NEXT: ret = TestingForm_OnNextButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PREVIOUS: ret = TestingForm_OnPreviousButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_LAST: ret = TestingForm_OnLastButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_SUBMIT: ret = TestingForm_OnSubmitButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL TestingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	EndDialog(hWnd, 0);
	return TRUE;
}

BOOL TestingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	WordCardHolder* wordCardHolder;
	WordCard* wordCard;
	TCHAR meaning[64];

	//단어첩 윈도우를 출력한다.
	wordCardHolderForm = FindWindow("#32770", "단어첩");
	wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
	wordCard = WordCardHolder_First(wordCardHolder);
	//단어 철자를 출력한다
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_SPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);

	return TRUE;
}

BOOL TestingForm_OnSubmitButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	TCHAR meaning[64];
	WordCardHolder* wordCardHolder;

	//2. 제출하기 버튼 누를 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1. 의미를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ANSWER), WM_GETTEXT, (WPARAM)64, (LPARAM)meaning);
		//2.2. 단어첩 윈도우를 찾는다.
		wordCardHolderForm = FindWindow("#32770", "단어첩");
		wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);

		//2.3. 단어첩 윈도우의 현재 단어카드의 의미와 입력한 의미랑 비교한다.
		//2.4. 찾았으면 해당 카드 의미를 출력한다.
		if (strcmp(wordCardHolder->current->word.meaning, meaning) == 0) {
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_CORRECTANSWER), WM_SETTEXT, (WPARAM)0, (LPARAM)meaning);
		}

		//2.5 못 찾았으면 틀린표시와 해당 카드 의미를 출력한다.
		else {
			//현재 edit control에 포커스를 준다.
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_ANSWER), WM_SETFOCUS, (WPARAM)0, (LPARAM)0);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_ANSWER), EM_SETSEL, (WPARAM)0, (LPARAM)-1);
			//윈도우 활성화를 해준다.
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_ANSWER), WM_ACTIVATE, (WPARAM)1, (LPARAM)WA_ACTIVE);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_CORRECTANSWER), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCardHolder->current->word.meaning);
		}
	}
	return TRUE;
}

BOOL TestingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	WordCardHolder* wordCardHolder;
	WordCard* wordCard;

	wordCardHolderForm = FindWindow("#32770", "단어첩");
	wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
	wordCard = WordCardHolder_First(wordCardHolder);

	SendMessage(GetDlgItem(hWnd, IDC_EDIT_ANSWER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_SPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_CORRECTANSWER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");

	return TRUE;
}

BOOL TestingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	WordCardHolder* wordCardHolder;
	WordCard* wordCard;

	wordCardHolderForm = FindWindow("#32770", "단어첩");
	wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
	wordCard = WordCardHolder_Previous(wordCardHolder);

	SendMessage(GetDlgItem(hWnd, IDC_EDIT_ANSWER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_SPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_CORRECTANSWER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");

	return TRUE;
}

BOOL TestingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	WordCardHolder* wordCardHolder;
	WordCard* wordCard;

	wordCardHolderForm = FindWindow("#32770", "단어첩");
	wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
	wordCard = WordCardHolder_Next(wordCardHolder);

	SendMessage(GetDlgItem(hWnd, IDC_EDIT_ANSWER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_SPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_CORRECTANSWER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");

	return TRUE;
}

BOOL TestingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	WordCardHolder* wordCardHolder;
	WordCard* wordCard;

	wordCardHolderForm = FindWindow("#32770", "단어첩");
	wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
	wordCard = WordCardHolder_Last(wordCardHolder);

	SendMessage(GetDlgItem(hWnd, IDC_EDIT_ANSWER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_SPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_CORRECTANSWER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");

	return TRUE;
}