#include "PuttingInForm.h"
#include "WordCardHolder.h"
#include "resource.h"
#include <stdlib.h>

BOOL CALLBACK PuttingInFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG: ret = PuttingInForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = PuttingInForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = PuttingInForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}

	return ret;
}

BOOL PuttingInForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR wordClassTypes[][8] = { "명사", "대명사", "동사", "형용사", "부사", "전치사", "접속사", "감탄사" };
	Long i;

	//1. 끼우기 윈도우가 생성될 때
	//1.1. 직책 목록을 만든다.
	for (i = 0; i < sizeof(wordClassTypes) / sizeof(wordClassTypes[0]); i++) {
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), CB_ADDSTRING, (WPARAM)0, (LPARAM)wordClassTypes[i]);
	}
	return TRUE;
}

BOOL PuttingInForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_BUTTON_PUTIN: ret = PuttingInForm_OnPutInButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL PuttingInForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//4. 닫기 버튼을 클릭했을 때
	//4.1. 끼우기 윈도우를 닫다.
	EndDialog(hWnd, 0);

	return TRUE;
}

BOOL PuttingInForm_OnPutInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCard wordCard;
	HWND wordCardHolderForm;
	WordCardHolder* wordCardHolder;
	WordCard* index;

	//3. 끼우기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1. 명함을 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_GETTEXT, (WPARAM)64, (LPARAM)wordCard.word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), WM_GETTEXT, (WPARAM)11, (LPARAM)wordCard.word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT, (WPARAM)64, (LPARAM)wordCard.word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)128, (LPARAM)wordCard.word.example);

		//3.2. 명함첩 윈도우를 찾는다.
		wordCardHolderForm = FindWindow("#32770", "단어첩");
		wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
		//3.3. 명함첩 윈도우의 명함첩에 끼운다.
		index = PutIn(wordCardHolder, wordCard);
		//3.4. 명함첩 윈도우에 명함을 출력한다.
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.spelling);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.wordClass);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.meaning);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.example);
		//3.5. 끼우기 윈도우를 닫는다.
		EndDialog(hWnd, 0);
	}
	return TRUE;
}