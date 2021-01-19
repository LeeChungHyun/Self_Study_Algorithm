#include "WordBookForm.h"
#include "resource.h"
#include "wordBook.h"
#include <stdlib.h>
#include <stdio.h>
#include <commctrl.h>
#pragma warning(disable:4996)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	int response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_WORDBOOKFORM), NULL, WordBookFormProc);
	return response;
}

BOOL CALLBACK WordBookFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (message) {
	case WM_INITDIALOG: ret = WordBookForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = WordBookForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY: ret = WordBookForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = WordBookForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL WordBookForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_RECORD: ret = WordBookForm_OnRecordButtonClicked(hWnd, wParam, lParam); break;
	//case IDC_BUTTON_FIND: ret = WordBookForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_CORRECT: ret = WordBookForm_OnCorrectButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ERASE: ret = WordBookForm_OnEraseButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ARRANGE: ret = WordBookForm_OnArrangeButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL WordBookForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (wParam) {
	case IDC_LIST_WORDS: ret = WordBookForm_OnListViewDoubleClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//1. 윈도우가 생성될 때
BOOL WordBookForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook* wordBook;
	Long count;
	LVCOLUMN column = { 0, };
	LVITEM item = { 0, };
	Long i;
	TCHAR number[64];
	TCHAR wordTypes[][8] = { "명사", "대명사", "동사", "형용사", "부사", "전치사", "접속사", "감탄사" };

	//1.1. 단어장을 만든다.
	wordBook = (WordBook*)malloc(sizeof(WordBook));
	Create(wordBook, 10000);
	SetWindowLong(hWnd, GWL_USERDATA, (Long)wordBook);

	//1.2. 적재하다.
	count = Load(wordBook);

	//1.3. 품사 목록을 만든다.
	for (i = 0; i < sizeof(wordTypes) / sizeof(wordTypes[0]); i++) {
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), CB_ADDSTRING, (WPARAM)0, (LPARAM)wordTypes[i]);
	}

	//1.4. 리스트뷰 컨트롤의 헤더를 만든다.
	column.mask = LVCF_WIDTH | LVCF_TEXT;

	column.cx = 50;
	column.pszText = "번호";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);

	column.cx = 150;
	column.pszText = "철자들";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);

	column.cx = 100;
	column.pszText = "품사";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);

	column.cx = 200;
	column.pszText = "의미";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);

	column.cx = 250;
	column.pszText = "예시";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);

	//1.5. 리스트뷰 컨트롤에 전체 선택을 설정한다.
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETEXTENDEDLISTVIEWSTYLE, (WPARAM)0, (LPARAM)LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//1.6. 개수만큼 리스트뷰 컨트롤에 항목들을 추가한다.
	item.mask = LVIF_TEXT;
	i = 0;
	while (i < count) {
		item.iItem = i;
		sprintf(number, "%d", i + 1);

		item.iSubItem = 0;
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

		item.iSubItem = 1;
		item.pszText = wordBook->words[i].spelling;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = wordBook->words[i].wordClass;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = wordBook->words[i].meaning;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = wordBook->words[i].example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);
		i++;
	}
	return TRUE;
}

//2. 기재하기 버튼을 클릭했을 때
BOOL WordBookForm_OnRecordButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook* wordBook;
	TCHAR number[64];
	TCHAR spelling[64];
	TCHAR wordClass[11];
	TCHAR meaning[64];
	TCHAR example[128];
	Long index;
	LVITEM item = { 0, };
	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1. 영단어를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_GETTEXT, (WPARAM)64, (LPARAM)spelling);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), WM_GETTEXT, (WPARAM)11, (LPARAM)wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT, (WPARAM)64, (LPARAM)meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)128, (LPARAM)example);

		//2.2. 단어장에서 기재한다.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Record(wordBook, spelling, wordClass, meaning, example);

		//2.3. 리스트뷰 컨트롤에 항목을 추가한다.
		item.mask = LVIF_TEXT;
		item.iItem = index;
		sprintf(number, "%d", index + 1);

		item.iSubItem = 0;
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

		item.iSubItem = 1;
		item.pszText = spelling;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = wordClass;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = meaning;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return TRUE;
}

/*
//3. 찾기 버튼을 클릭했을 때
BOOL WordBookForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1. 찾기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), NULL, FindingFormProc);
	}
	return TRUE;
}
*/

//4. 고치기 버튼을 클릭했을 때
BOOL WordBookForm_OnCorrectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR wordClass[11];
	TCHAR meaning[64];
	TCHAR example[128];
	Long index;
	WordBook* wordBook;
	LVITEM item = { 0, };
	if (HIWORD(wParam) == BN_CLICKED) {
		//4.1. 영단어를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), WM_GETTEXT, (WPARAM)11, (LPARAM)wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT, (WPARAM)64, (LPARAM)meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)128, (LPARAM)example);

		//4.2. 리스트뷰 컨트롤의 선택된 항목의 위치를 읽는다.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//4.3. 단어장에서 고치다.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Correct(wordBook, index, wordClass, meaning, example);

		//4.4. 리스트뷰 컨트롤의 항목을 고치다.
		item.mask = LVIF_TEXT;
		item.iItem = index;

		item.iSubItem = 2;
		item.pszText = wordBook->words[index].wordClass;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = wordBook->words[index].meaning;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = wordBook->words[index].example;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return TRUE;
}

//5. 지우기 버튼을 클릭했을 때
BOOL WordBookForm_OnEraseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long index;
	WordBook* wordBook;
	LVITEM item = { 0, };
	Long i;
	TCHAR number[64];
	if (HIWORD(wParam) == BN_CLICKED) {
		//5.1. 리스트뷰 컨트롤의 선택된 항목의 위치를 읽는다.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);
		//5.2. 단어장에서 지운다.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		Erase(wordBook, index);
			//5.3. 리스트뷰 컨트롤의 항목을 지운다.
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_DELETEITEM, (WPARAM)index, (LPARAM)0);

			//5.4. 선택된 위치부터 마지막 줄까지 번호를 고친다.
			item.iSubItem = 0;
			i = index;
			while (i < wordBook->length) {
				sprintf(number, "%d", i + 1);
				item.iItem = i;
				item.pszText = number;
				SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
				i++;
			}
	}
	return TRUE;
}

//6. 정리하기 버튼을 클릭했을 때
BOOL WordBookForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook* wordBook;
	Long i;
	TCHAR number[64];
	LVITEM item = { 0, };
	if (HIWORD(wParam) == BN_CLICKED) {
		//6.1. 단어장에서 정리한다.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		Arrange(wordBook);

		//6.2. 리스트뷰 컨트롤의 모든 항목을 지운다.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);

		//6.3. 단어장에 적힌 줄 수만큼 리스트뷰 컨트롤의 항목을 추가한다.
		item.mask = LVIF_TEXT;
		i = 0;
		while (i < wordBook->length) {
			sprintf(number, "%d", i + 1);
			item.iItem = i;

			item.iSubItem = 0;
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

			item.iSubItem = 1;
			item.pszText = wordBook->words[i].spelling;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 2;
			item.pszText = wordBook->words[i].wordClass;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 3;
			item.pszText = wordBook->words[i].meaning;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 4;
			item.pszText = wordBook->words[i].example;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);
			i++;
		}
	}
	return TRUE;
}

//7. 리스트뷰 컨트롤의 항목을 더블클릭했을 때
BOOL WordBookForm_OnListViewDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long index;
	LVITEM item = { 0, };
	TCHAR spelling[64];
	TCHAR wordClass[11];
	TCHAR meaning[64];
	TCHAR example[128];
	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
		//7.1. 리스트뷰 컨트롤의 선택된 위치를 읽는다.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//7.2. 선택된 위치의 항목을 읽는다.
		item.mask = LVIF_TEXT;
		item.iItem = index;

		item.iSubItem = 1;
		item.pszText = spelling;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = wordClass;
		item.cchTextMax = 11;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = meaning;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = example;
		item.cchTextMax = 128;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		//7.3. 영단어에 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)spelling);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)example);
	}
	return TRUE;
}

//8. 닫기 버튼을 클릭했을 때
BOOL WordBookForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook* wordBook;
	//8.1. 저장한다.
	wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);

	if (wordBook != NULL) {
		Save(wordBook);
		//8.2. 단어장을 없앤다.
		Destroy(wordBook);
		free(wordBook);
	}
	//8.3. 윈도우를 닫는다.
	EndDialog(hWnd, 0);
	return TRUE;
}