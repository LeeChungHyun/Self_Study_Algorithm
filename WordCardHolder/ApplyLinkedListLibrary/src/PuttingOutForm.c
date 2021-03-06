#include "PuttingOutForm.h"
#include "WordCardHolder.h"
#include "resource.h"

BOOL CALLBACK PuttingOutFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (message) {
	case WM_INITDIALOG: ret = PuttingOutForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = PuttingOutForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return	ret;
}

BOOL PuttingOutForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	WordCardHolder* wordCardHolder;
	WordCard wordCard;
	WordCard* index;
	//명함꽂이 윈도우를 찾는다
	wordCardHolderForm = FindWindow("#32770", "단어첩");
	wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
	//명함을 꽂는다
	wordCard = PutOut(wordCardHolder, wordCardHolder->current);
	//들어내기 윈도우에 명함을 출력한다
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard.word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard.word.wordClass);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard.word.meaning);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard.word.example);
	//명함꽂이 윈도우의 명함꽂이에 명함이 있으면 명함곶이 윈도우에 명함을 출력한다.
	if (wordCardHolder->current != NULL) {
		index = wordCardHolder->current;
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.spelling);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.wordClass);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.meaning);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.example);

	}
	else {
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	}
	return TRUE;
}

BOOL PuttingOutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	WordCardHolder* wordCardHolder;
	WordCard wordCard;
	WordCard* index;
	int ret;
	ret = MessageBox(hWnd, (LPCWSTR)"끼우시겠습니까?", (LPCWSTR)"알림", MB_YESNOCANCEL | MB_ICONEXCLAMATION);
	switch (ret) {
		//2.2. 예 버튼을 클릭했을 때
	case IDYES:
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_GETTEXT, (WPARAM)64, (LPARAM)wordCard.word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_GETTEXT, (WPARAM)12, (LPARAM)wordCard.word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_GETTEXT, (WPARAM)64, (LPARAM)wordCard.word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_GETTEXT, (WPARAM)128, (LPARAM)wordCard.word.example);
		//2.2.1. 명함꽂이 윈도우를 찾는다.
		wordCardHolderForm = FindWindow("#32770", "단어첩");
		wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
		//2.2.2. 명함꽂이 윈도우의 명함첩에 끼운다.
		index = PutIn(wordCardHolder, wordCard);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.spelling);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.wordClass);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.meaning);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.example);
		//2.2.4. 들어내기 윈도우를 닫는다.
		EndDialog(hWnd, 0);
		break;
		//2.3. 아니오 버튼을 클릭했을 때
	case IDNO:
		//2.3.1. 들어내기 윈도우를 닫는다.
		EndDialog(hWnd, 0);
		break;
	default:
		break;
	}
	return TRUE;
}