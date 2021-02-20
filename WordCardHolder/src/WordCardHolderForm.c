#include "WordCardHolderForm.h"
#include "PuttingInForm.h"
#include "FindingForm.h"
#include "PuttingOutForm.h"
#include "MemorizingForm.h"
#include "KeepingForm.h"
#include "TestingForm.h"
#include "WordCardHolderh.h"
#include "resource.h"
#include <stdlib.h>
#include <commctrl.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	int response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_WORDCARDHOLDERFORM), NULL, WordCardHolderFormProc);
	return response;
}

BOOL CALLBACK WordCardHolderFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG: ret = WordCardHolderForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = WordCardHolderForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = WordCardHolderForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL WordCardHolderForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCardHolder* wordCardHolder;
	WordCardHolder* keepCardHolder;
	Long count;
	Long keepCount;
	WordCard* index;
	//1. 윈도우가 생성될 때
	//1.1. 단어첩을 생성하다.
	wordCardHolder = (WordCardHolder*)malloc(sizeof(WordCardHolder));
	Create(wordCardHolder);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)wordCardHolder);

	//1.2 찜한 단어첩을 생성하다.
	keepCardHolder = (WordCardHolder*)malloc(sizeof(WordCardHolder));
	Create(keepCardHolder);
	SetProp(hWnd, "PROP_KEEPCARDHOLDER", (HANDLE)keepCardHolder);

	//단어첩을 적재한다.
	count = Load(wordCardHolder);

	//찜한 단어첩을 적재한다
	keepCount = KeepingCardLoad(keepCardHolder);
	SetProp(hWnd, "PROP_KEEPCOUNT", (HANDLE)keepCount);

	
	//적재할때 첫번째 단어를 보이도록 한다.
	if (count > 0) {
		index = First(wordCardHolder);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.example);
	}
	return TRUE;
}

BOOL WordCardHolderForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_BUTTON_PUTIN: ret = WordCardHolderForm_OnPutInButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIND: ret = WordCardHolderForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PUTOUT: ret = WordCardHolderForm_OnPutOutButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ARRANGE: ret = WordCardHolderForm_OnArrangeButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIRST: ret = WordCardHolderForm_OnFirstButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PREVIOUS: ret = WordCardHolderForm_OnPreviousButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_NEXT: ret = WordCardHolderForm_OnNextButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_LAST: ret = WordCardHolderForm_OnLastButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_MEMORIZE: ret = WordCardHolderForm_OnMemorizeButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_KEEP: ret = WordCardHolderForm_OnKeepButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_TEST: ret = WordCardHolderForm_OnTestButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL WordCardHolderForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCardHolder* wordCardHolder;
	WordCardHolder* keepCardHolder;

	//10. 닫기 버튼을 클릭했을 때

	//10.1. 단어첩을 지우다.
	wordCardHolder = (WordCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
	keepCardHolder = (Long)GetProp(hWnd, "PROP_KEEPCARDHOLDER");
	
	if (wordCardHolder != NULL) {
		//단어첩과 찜한 단어첩을 저장한다.
		Save(wordCardHolder);
		KeepingCardSave(keepCardHolder);
		Destroy(wordCardHolder);
		Destroy(keepCardHolder);
		free(wordCardHolder);
		free(keepCardHolder);
	}
	RemoveProp(hWnd, "PROP_KEEPCARDHOLDER");
	//10.2. 윈도우를 닫다.
	EndDialog(hWnd, 0);
	return TRUE;
}


BOOL WordCardHolderForm_OnPutInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//2. 끼우기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1. 끼우기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_PUTTINGINFORM), NULL, PuttingInFormProc);
	}

	return TRUE;
}

BOOL WordCardHolderForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//3. 찾기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1. 찾기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), NULL, FindingFormProc);
	}
	return TRUE;
}

BOOL WordCardHolderForm_OnPutOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//4. 들어내기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//4.1. 들어내기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_PUTTINGOUTFORM), NULL, PuttingOutFormProc);
	}
	return TRUE;
}

BOOL WordCardHolderForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCardHolder* wordCardHolder;
	WordCard* wordCard;

	//5. 정리하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		wordCardHolder = (WordCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		//5.1. 단어첩에서 정리하다.
		Arrange(wordCardHolder);
		//5.2. 단어첩에서 처음으로 이동한다.
		wordCard = First(wordCardHolder);
		//5.3. 단어을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.example);
	}
	return TRUE;
}

BOOL WordCardHolderForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCardHolder* wordCardHolder;
	WordCard* wordCard;

	//6. 처음 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		wordCardHolder = (WordCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		//6.1. 단어첩에서 처음으로 이동하다.
		wordCard = First(wordCardHolder);
		//6.2. 단어을 출력하다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.example);
	}
	return TRUE;
}

BOOL WordCardHolderForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCardHolder* wordCardHolder;
	WordCard* wordCard;

	if (HIWORD(wParam) == BN_CLICKED) {
		wordCardHolder = (WordCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		
		wordCard = Previous(wordCardHolder);
		
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.example);
	}
	return TRUE;
}

BOOL WordCardHolderForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCardHolder* wordCardHolder;
	WordCard* wordCard;

	if (HIWORD(wParam) == BN_CLICKED) {
		wordCardHolder = (WordCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);

		wordCard = Next(wordCardHolder);

		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.example);
	}
	return TRUE;
}

BOOL WordCardHolderForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCardHolder* wordCardHolder;
	WordCard* wordCard;

	if (HIWORD(wParam) == BN_CLICKED) {
		wordCardHolder = (WordCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);

		wordCard = Last(wordCardHolder);

		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.example);
	}
	return TRUE;
}

BOOL WordCardHolderForm_OnMemorizeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	if (HIWORD(wParam) == BN_CLICKED) {
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_MEMORIZINGFORM), NULL, MemorizingFormProc);
	}
	return TRUE;
}

BOOL WordCardHolderForm_OnKeepButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	if (HIWORD(wParam) == BN_CLICKED) {
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_KEEPINGFORM), NULL, KeepingFormProc);
	}
	return TRUE;
}

BOOL WordCardHolderForm_OnTestButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	if (HIWORD(wParam) == BN_CLICKED) {
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_TESTINGFORM), NULL, TestingFormProc);
	}
	return TRUE;
}