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

//1. �����찡 ������ ��
BOOL WordBookForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook* wordBook;
	Long count;
	LVCOLUMN column = { 0, };
	LVITEM item = { 0, };
	Long i;
	TCHAR number[64];
	TCHAR wordTypes[][8] = { "���", "����", "����", "�����", "�λ�", "��ġ��", "���ӻ�", "��ź��" };

	//1.1. �ܾ����� �����.
	wordBook = (WordBook*)malloc(sizeof(WordBook));
	Create(wordBook, 10000);
	SetWindowLong(hWnd, GWL_USERDATA, (Long)wordBook);

	//1.2. �����ϴ�.
	count = Load(wordBook);

	//1.3. ǰ�� ����� �����.
	for (i = 0; i < sizeof(wordTypes) / sizeof(wordTypes[0]); i++) {
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), CB_ADDSTRING, (WPARAM)0, (LPARAM)wordTypes[i]);
	}

	//1.4. ����Ʈ�� ��Ʈ���� ����� �����.
	column.mask = LVCF_WIDTH | LVCF_TEXT;

	column.cx = 50;
	column.pszText = "��ȣ";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);

	column.cx = 150;
	column.pszText = "ö�ڵ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);

	column.cx = 100;
	column.pszText = "ǰ��";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);

	column.cx = 200;
	column.pszText = "�ǹ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);

	column.cx = 250;
	column.pszText = "����";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);

	//1.5. ����Ʈ�� ��Ʈ�ѿ� ��ü ������ �����Ѵ�.
	SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_SETEXTENDEDLISTVIEWSTYLE, (WPARAM)0, (LPARAM)LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//1.6. ������ŭ ����Ʈ�� ��Ʈ�ѿ� �׸���� �߰��Ѵ�.
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

//2. �����ϱ� ��ư�� Ŭ������ ��
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
		//2.1. ���ܾ �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_GETTEXT, (WPARAM)64, (LPARAM)spelling);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), WM_GETTEXT, (WPARAM)11, (LPARAM)wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT, (WPARAM)64, (LPARAM)meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)128, (LPARAM)example);

		//2.2. �ܾ��忡�� �����Ѵ�.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Record(wordBook, spelling, wordClass, meaning, example);

		//2.3. ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
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
//3. ã�� ��ư�� Ŭ������ ��
BOOL WordBookForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1. ã�� �����츦 ����Ѵ�.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), NULL, FindingFormProc);
	}
	return TRUE;
}
*/

//4. ��ġ�� ��ư�� Ŭ������ ��
BOOL WordBookForm_OnCorrectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR wordClass[11];
	TCHAR meaning[64];
	TCHAR example[128];
	Long index;
	WordBook* wordBook;
	LVITEM item = { 0, };
	if (HIWORD(wParam) == BN_CLICKED) {
		//4.1. ���ܾ �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), WM_GETTEXT, (WPARAM)11, (LPARAM)wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT, (WPARAM)64, (LPARAM)meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)128, (LPARAM)example);

		//4.2. ����Ʈ�� ��Ʈ���� ���õ� �׸��� ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//4.3. �ܾ��忡�� ��ġ��.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Correct(wordBook, index, wordClass, meaning, example);

		//4.4. ����Ʈ�� ��Ʈ���� �׸��� ��ġ��.
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

//5. ����� ��ư�� Ŭ������ ��
BOOL WordBookForm_OnEraseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long index;
	WordBook* wordBook;
	LVITEM item = { 0, };
	Long i;
	TCHAR number[64];
	if (HIWORD(wParam) == BN_CLICKED) {
		//5.1. ����Ʈ�� ��Ʈ���� ���õ� �׸��� ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);
		//5.2. �ܾ��忡�� �����.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		Erase(wordBook, index);
			//5.3. ����Ʈ�� ��Ʈ���� �׸��� �����.
			SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_DELETEITEM, (WPARAM)index, (LPARAM)0);

			//5.4. ���õ� ��ġ���� ������ �ٱ��� ��ȣ�� ��ģ��.
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

//6. �����ϱ� ��ư�� Ŭ������ ��
BOOL WordBookForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook* wordBook;
	Long i;
	TCHAR number[64];
	LVITEM item = { 0, };
	if (HIWORD(wParam) == BN_CLICKED) {
		//6.1. �ܾ��忡�� �����Ѵ�.
		wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);
		Arrange(wordBook);

		//6.2. ����Ʈ�� ��Ʈ���� ��� �׸��� �����.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);

		//6.3. �ܾ��忡 ���� �� ����ŭ ����Ʈ�� ��Ʈ���� �׸��� �߰��Ѵ�.
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

//7. ����Ʈ�� ��Ʈ���� �׸��� ����Ŭ������ ��
BOOL WordBookForm_OnListViewDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	Long index;
	LVITEM item = { 0, };
	TCHAR spelling[64];
	TCHAR wordClass[11];
	TCHAR meaning[64];
	TCHAR example[128];
	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
		//7.1. ����Ʈ�� ��Ʈ���� ���õ� ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_WORDS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//7.2. ���õ� ��ġ�� �׸��� �д´�.
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

		//7.3. ���ܾ ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)spelling);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)example);
	}
	return TRUE;
}

//8. �ݱ� ��ư�� Ŭ������ ��
BOOL WordBookForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordBook* wordBook;
	//8.1. �����Ѵ�.
	wordBook = (WordBook*)GetWindowLong(hWnd, GWL_USERDATA);

	if (wordBook != NULL) {
		Save(wordBook);
		//8.2. �ܾ����� ���ش�.
		Destroy(wordBook);
		free(wordBook);
	}
	//8.3. �����츦 �ݴ´�.
	EndDialog(hWnd, 0);
	return TRUE;
}