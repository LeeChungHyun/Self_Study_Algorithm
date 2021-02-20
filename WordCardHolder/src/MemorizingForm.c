#include "MemorizingForm.h"
#include "resource.h"
#include "WordCardHolderh.h"
#include <stdlib.h>
#include <stdio.h>
#include <CommCtrl.h>
#pragma warning(disable:4996)

BOOL CALLBACK MemorizingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (message) {
	case WM_INITDIALOG: ret = MemorizingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = MemorizingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = MemorizingForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL MemorizingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_FIRST: ret = MemorizingForm_OnFirstButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_NEXT: ret = MemorizingForm_OnNextButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PREVIOUS: ret = MemorizingForm_OnPreviousButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_LAST: ret = MemorizingForm_OnLastButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_KEEP: ret = MemorizingForm_OnKeepButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL MemorizingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	RemoveProp(hWnd, "PROP_KEEPCARDHOLDER");
	RemoveProp(hWnd, "PROP_INDEX");
	EndDialog(hWnd, 0);
	return TRUE;
}

BOOL MemorizingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	WordCardHolder* wordCardHolder;
	WordCard* wordCard;

	wordCardHolderForm = FindWindow("#32770", "단어첩");
	wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
	wordCard = First(wordCardHolder);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_SPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.meaning);
	
	return TRUE;
}

BOOL MemorizingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	WordCardHolder* wordCardHolder;
	WordCard* wordCard;

	wordCardHolderForm = FindWindow("#32770", "단어첩");
	wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
	wordCard = First(wordCardHolder);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_SPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.meaning);
	
	return TRUE;
}

BOOL MemorizingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	WordCardHolder* wordCardHolder;
	WordCard* wordCard;

	wordCardHolderForm = FindWindow("#32770", "단어첩");
	wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
	wordCard = Previous(wordCardHolder);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_SPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.meaning);

	return TRUE;
}

BOOL MemorizingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	WordCardHolder* wordCardHolder;
	WordCard* wordCard;

	wordCardHolderForm = FindWindow("#32770", "단어첩");
	wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
	wordCard = Next(wordCardHolder);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_SPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.meaning);
	
	return TRUE;
}

BOOL MemorizingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	WordCardHolder* wordCardHolder;
	WordCard* wordCard;

	wordCardHolderForm = FindWindow("#32770", "단어첩");
	wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
	wordCard = Last(wordCardHolder);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_SPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.meaning);

	return TRUE;
}

BOOL MemorizingForm_OnKeepButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	HWND keepCardHolderForm;
	WordCardHolder* wordCardHolder;
	WordCardHolder* keepCardHolder;
	WordCard wordCard;
	WordCard* index;
	int ret;

	if (HIWORD(wParam)==BN_CLICKED) {
		//1.알림을 출력한다.
		ret = MessageBox(hWnd, (LPCWSTR)"찜하시겠습니까?", (LPCWSTR)"찜하기", MB_YESNO | MB_ICONEXCLAMATION);

		switch (ret) {
			//2.네라고 누를시
		case IDYES:
			//2.1 단어첩 윈도우를 찾는다
			wordCardHolderForm = FindWindow("#32770", "단어첩");
			wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);

			//2.2 단어첩 윈도우에서 해당 카드를 들어낸다.
			wordCard = PutOut(wordCardHolder, wordCardHolder->current);

			//2.3 찜한 단어첩을 불러온다
			keepCardHolderForm = FindWindow("#32770", "단어첩");
			keepCardHolder = (Long)GetProp(keepCardHolderForm, "PROP_KEEPCARDHOLDER");

			//2.4 찜한 단어첩에서 해당 카드를 꽂는다.
			index = PutIn(keepCardHolder, wordCard);
			SetProp(keepCardHolderForm, "PROP_INDEX", (HANDLE)index);

			SendMessage(GetDlgItem(hWnd, IDC_STATIC_SPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_WORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_EXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)"");

			//2.5 알림을 출력한다.
			MessageBox(hWnd, (LPCWSTR)"찜했습니다", (LPCWSTR)"찜하기", MB_OK);
			break;

		case IDNO:
			break;

		default: break;
		}
	}
	return TRUE;
}