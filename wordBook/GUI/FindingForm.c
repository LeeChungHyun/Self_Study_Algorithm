#include "FindingForm.h"
#include "resource.h"
#include "wordBook.h"
#include <stdio.h>
#include <stdlib.h>
#include <commctrl.h>
#pragma warning(disable:4996)

BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG: ret = FindingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = FindingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY: ret = FindingForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = FindingForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_BUTTON_FIND: ret = FindingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL FindingForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (wParam) {
	case IDC_LIST_WORDS: ret = FindingForm_OnListViewDoubleClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//1. 찾기 윈도우가 생성될 때
BOOL FindingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	LVCOLUMN column = { 0, };

	//1.1. 리스트뷰 컨트롤의 헤더를 만든다.
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

	//1.2. 조건을 체크한다.
	SendMessage(GetDlgItem(hWnd, IDC_RADIO_FINDSPELLING), BM_SETCHECK, (WPARAM)BST_CHECKED, (LPARAM)0);
	SendMessage(GetDlgItem(hWnd, IDC_RADIO_FINDMEANING), BM_SETCHECK, (WPARAM)BST_UNCHECKED, (LPARAM)0);

	//1.3. 리스트뷰 컨트롤에 전체 선택을 설정한다.
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETEXTENDEDLISTVIEWSTYLE, (WPARAM)0, (LPARAM)LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return TRUE;
}

//4. 닫기 버튼을 클릭시
BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long(*indexes);
	indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
	//7.1 찾기 윈도우를 닫는다
	if (indexes != NULL) {
		free(indexes);
	}
	EndDialog(hWnd, 0);
	return TRUE;
}

//2. 찾기버튼을 클릭했을 때
BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR spelling[64];
	TCHAR meaning[64];
	HWND wordBookForm;
	WordBook* wordBook;
	Long(*indexes);
	Long count;
	LVITEM item = { 0, };
	Long i;
	TCHAR number[64];

	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1. 단어를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_FINDSPELLING), WM_GETTEXT, (WPARAM)64, (LPARAM)spelling);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_FINDMEANING), WM_GETTEXT, (WPARAM)64, (LPARAM)meaning);
		int spellingChecked = SendMessage(GetDlgItem(hWnd, IDC_RADIO_FINDSPELLING), BM_GETCHECK, (WPARAM)0, (LPARAM)0);
		int meaningChecked = SendMessage(GetDlgItem(hWnd, IDC_RADIO_FINDMEANING), BM_GETCHECK, (WPARAM)0, (LPARAM)0);

		//2.2. 단어장 윈도우를 찾는다.
		wordBookForm = FindWindow("#32770", "단어장");
		wordBook = (WordBook*)GetWindowLong(wordBookForm, GWL_USERDATA);

		//2.3. 단어장 윈도우의 단어장에서  조건에 따라 찾는다.
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		if (indexes != NULL) {
			free(indexes);
		}

		if (spellingChecked == BST_CHECKED && meaningChecked == BST_UNCHECKED) {
			FindSpelling(wordBook, spelling, &indexes, &count);
		}
		else if (spellingChecked == BST_UNCHECKED && meaningChecked == BST_CHECKED) {
			FindMeaning(wordBook, meaning, &indexes, &count);
		}

		SetWindowLong(hWnd, GWL_USERDATA, (LONG)indexes);

		//2.4. 리스트뷰 컨트롤의 모든 항목을 지운다.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);

		//2.5. 리스트뷰 컨트롤에 찾은 개수만큼 항목을 추가한다.
		item.mask = LVIF_TEXT;
		i = 0;
		while (i < count) {
			sprintf(number, "%d", i + 1);
			item.iItem = i;

			item.iSubItem = 0;
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

			item.iSubItem = 1;
			item.pszText = wordBook->words[indexes[i]].spelling;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 2;
			item.pszText = wordBook->words[indexes[i]].wordClass;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 3;
			item.pszText = wordBook->words[indexes[i]].meaning;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 4;
			item.pszText = wordBook->words[indexes[i]].example;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);
			i++;
		}
	}
	return TRUE;
}

//3. 리스트뷰 컨트롤의 항목을 더블클릭했을 때
BOOL FindingForm_OnListViewDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long index;
	LVITEM item = { 0, };
	TCHAR spelling[64];
	TCHAR wordClass[11];
	TCHAR meaning[64];
	TCHAR example[128];
	HWND wordBookForm;
	Long(*indexes);

	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
		//3.1. 리스트뷰 컨트롤의 선택된 항목의 위치를 읽는다.
		index = SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//3.2. 선택된 위치의 항목을 읽는다.
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

		//3.3. 단어장 윈도우를 찾는다.
		wordBookForm = FindWindow("#32770", "단어장");

		//3.4. 단어장 윈도우의 영단어에 출력한다.
		SendMessage(GetDlgItem(wordBookForm, IDC_EDIT_SPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)spelling);
		SendMessage(GetDlgItem(wordBookForm, IDC_COMBO_WORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordClass);
		SendMessage(GetDlgItem(wordBookForm, IDC_EDIT_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)meaning);
		SendMessage(GetDlgItem(wordBookForm, IDC_EDIT_EXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)example);

		//3.5. 단어장 윈도우의 리스트뷰 컨트롤의 항목을 선택한다.
		indexes = (Long(*))GetWindowLong(hWnd, GWL_USERDATA);
		SendMessage(GetDlgItem(wordBookForm, IDC_LIST_WORDS), LVM_SETSELECTIONMARK, (WPARAM)0, (LPARAM)indexes[index]);

		//3.6. 찾기 윈도우를 닫는다.
		if (indexes != NULL) {
			free(indexes);
		}
		EndDialog(hWnd, 0);
	}
	return TRUE;
}