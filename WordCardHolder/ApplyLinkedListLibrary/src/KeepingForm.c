#include "KeepingForm.h"
#include "resource.h"
#include "WordCardHolder.h"
#include <stdlib.h>
#include <stdio.h>
#include <CommCtrl.h>
#pragma warning(disable:4996)

BOOL CALLBACK KeepingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (message) {
	case WM_INITDIALOG: ret = KeepingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = KeepingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = KeepingForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL KeepingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_FIRST: ret = KeepingForm_OnFirstButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_NEXT: ret = KeepingForm_OnNextButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PREVIOUS: ret = KeepingForm_OnPreviousButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_LAST: ret = KeepingForm_OnLastButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_GETOUT: ret = KeepingForm_OnGetOutButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL KeepingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	RemoveProp(hWnd, "PROP_KEEPCARDHOLDER");
	RemoveProp(hWnd, "PROP_INDEX");
	RemoveProp(hWnd, "PROP_KEEPCOUNT");
	EndDialog(hWnd, 0);
	return TRUE;
}

BOOL KeepingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	WordCard* index;
	WordCardHolder* keepCardHolder;
	Long keepCount;

	//1. 단어첩 윈도우를 출력한다.
	wordCardHolderForm = FindWindow("#32770", "단어첩");

	//2.찜한 단어첩을 불러온다
	keepCardHolder = (Long)GetProp(wordCardHolderForm, "PROP_KEEPCARDHOLDER");
	keepCount = (Long)GetProp(wordCardHolderForm, "PROP_KEEPCOUNT");

	index = WordCardHolder_First(keepCardHolder);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.wordClass);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.meaning);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.example);
	SetProp(hWnd, "PROP_INDEX", (HANDLE)index);
	SetProp(hWnd, "PROP_KEEPCARDHOLDER", (HANDLE)keepCardHolder);

	if (keepCount > 0) {
		index = WordCardHolder_First(keepCardHolder);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.example);

		SetProp(hWnd, "PROP_INDEX", (HANDLE)index);
		SetProp(hWnd, "PROP_KEEPCARDHOLDER", (HANDLE)keepCardHolder);
	}
	return TRUE;
}

BOOL KeepingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCardHolder* keepCardHolder;
	WordCard* index;

	index = (Long)GetProp(hWnd, "PROP_INDEX");
	keepCardHolder = (Long)GetProp(hWnd, "PROP_KEEPCARDHOLDER");
	index = WordCardHolder_First(keepCardHolder);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.wordClass);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.meaning);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.example);
	SetProp(hWnd, "PROP_INDEX", (HANDLE)index);
	SetProp(hWnd, "PROP_KEEPCARDHOLDER", (HANDLE)keepCardHolder);
	return TRUE;
}

BOOL KeepingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCardHolder* keepCardHolder;
	WordCard* index;

	index = (Long)GetProp(hWnd, "PROP_INDEX");
	keepCardHolder = (Long)GetProp(hWnd, "PROP_KEEPCARDHOLDER");
	index = WordCardHolder_Previous(keepCardHolder);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.wordClass);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.meaning);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.example);

	SetProp(hWnd, "PROP_INDEX", (HANDLE)index);
	SetProp(hWnd, "PROP_KEEPCARDHOLDER", (HANDLE)keepCardHolder);
	return TRUE;
}

BOOL KeepingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCardHolder* keepCardHolder;
	WordCard* index;

	keepCardHolder = (Long)GetProp(hWnd, "PROP_KEEPCARDHOLDER");
	index = (Long)GetProp(hWnd, "PROP_INDEX");
	index = WordCardHolder_Next(keepCardHolder);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.wordClass);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.meaning);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.example);
	SetProp(hWnd, "PROP_INDEX", (HANDLE)index);
	SetProp(hWnd, "PROP_KEEPCARDHOLDER", (HANDLE)keepCardHolder);

	return TRUE;
}

BOOL KeepingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCardHolder* keepCardHolder;
	WordCard* index;

	index = (Long)GetProp(hWnd, "PROP_INDEX");
	keepCardHolder = (Long)GetProp(hWnd, "PROP_KEEPCARDHOLDER");
	index = WordCardHolder_Last(keepCardHolder);

	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.wordClass);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.meaning);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.example);
	SetProp(hWnd, "PROP_INDEX", (HANDLE)index);
	SetProp(hWnd, "PROP_KEEPCARDHOLDER", (HANDLE)keepCardHolder);

	return TRUE;
}

BOOL KeepingForm_OnGetOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	HWND keepCardHolderForm;
	WordCardHolder* wordCardHolder;
	WordCardHolder* keepCardHolder;
	WordCard wordCard;
	WordCard* index;

	//되돌리기 버튼 클릭시
	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1 단어첩 윈도우를 찾는다
		keepCardHolderForm = FindWindow("#32770", "단어첩");
		keepCardHolder = (Long)GetProp(keepCardHolderForm, "PROP_KEEPCARDHOLDER");

		//2.2  찜한 단어첩 윈도우에서 해당 카드를 들어낸다.
		wordCard = PutOut(keepCardHolder, keepCardHolder->current);

		//2.3 단어첩 윈도우를 불러온다
		wordCardHolderForm = FindWindow("#32770", "단어첩");
		wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);

		//2.4 찜한 단어첩에서 해당 카드를 꽂는다.
		index = PutIn(wordCardHolder, wordCard);
		SetProp(wordCardHolderForm, "PROP_INDEX", (HANDLE)index);

		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		MessageBox(hWnd, (LPCWSTR)"되돌렸습니다", (LPCWSTR)"되돌리기", MB_OK);
	}
	return TRUE;
}