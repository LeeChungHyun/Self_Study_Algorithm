#include "WordCardHolderh.h"
#include "FindingForm.h"
#include "resource.h"
#include <stdlib.h>

BOOL CALLBACK FindingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret = NULL;
	switch (message) {
	case WM_INITDIALOG: ret = FindingForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = FindingForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = FindingForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL FindingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_FIND: ret = FindingForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_SELECT: ret = FindingForm_OnSelectButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIRST: ret = FindingForm_OnFirstButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_NEXT2: ret = FindingForm_OnNextButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PREVIOUS2: ret = FindingForm_OnPreviousButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_LAST2: ret = FindingForm_OnLastButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

BOOL FindingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	SendMessage(GetDlgItem(hWnd, IDC_RADIO_SPELLING), BM_SETCHECK, (WPARAM)BST_CHECKED, (LPARAM)0);
	SendMessage(GetDlgItem(hWnd, IDC_RADIO_MEANING), BM_SETCHECK, (WPARAM)BST_UNCHECKED, (LPARAM)0);
	return TRUE;
}

BOOL FindingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCard* (*indexes);
	indexes = (WordCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
	if (indexes != NULL) {
		free(indexes);
	}
	RemoveProp(hWnd, "PROP_CURRENT");
	RemoveProp(hWnd, "PROP_COUNT");
	EndDialog(hWnd, 0);
	return TRUE;
}

BOOL FindingForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	WordCard* wordCard;
	WordCard* (*indexes);
	WordCardHolder* wordCardHolder;
	Long count;
	Long current;
	TCHAR spelling[64];
	TCHAR meaning[64];

	if (HIWORD(wParam) == BN_CLICKED) {

		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_GETTEXT, (WPARAM)64, (LPARAM)spelling);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT, (WPARAM)64, (LPARAM)meaning);

		int spellingChecked = SendMessage(GetDlgItem(hWnd, IDC_RADIO_SPELLING), BM_GETCHECK, (WPARAM)0, (LPARAM)0);
		int meaningChecked = SendMessage(GetDlgItem(hWnd, IDC_RADIO_MEANING), BM_GETCHECK, (WPARAM)0, (LPARAM)0);

		wordCardHolderForm = FindWindow("#32770", "단어첩");
		wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);

		indexes = (WordCardHolder * (*))GetWindowLong(hWnd, GWL_USERDATA);
		if (indexes != NULL) {
			free(indexes);
		}

		if (spellingChecked == BST_CHECKED && meaningChecked == BST_UNCHECKED) {
			FindSpelling(wordCardHolder, spelling, &indexes, &count);
		}

		else if (spellingChecked == BST_UNCHECKED && meaningChecked == BST_CHECKED) {
			FindMeaning(wordCardHolder, meaning, &indexes, &count);
		}

		if (count > 0) {
			current = 0;
			wordCard = indexes[current];
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.wordClass);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.meaning);
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.example);

			SetWindowLong(hWnd, GWL_USERDATA, (LONG)indexes);
			SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);
			SetProp(hWnd, "PROP_COUNT", (HANDLE)count);
		}
		else {
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		}
	}
	return TRUE;
}

BOOL FindingForm_OnSelectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	HWND wordCardHolderForm;
	WordCard* wordCard;
	WordCard* (*indexes);
	WordCardHolder* wordCardHolder;
	Long current;

	if (HIWORD(wParam) == BN_CLICKED) {
		indexes = (WordCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");
		wordCard = indexes[current];

		wordCardHolderForm = FindWindow("#32770", "단어첩");
		wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
		wordCard = Move(wordCardHolder, wordCard);

		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.wordClass);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.meaning);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.example);
		
		if (indexes != NULL) {
			free(indexes);
		}

		RemoveProp(hWnd, "PROP_CURRENT");
		RemoveProp(hWnd, "PROP_COUNT");
		EndDialog(hWnd, 0);
	}
	return TRUE;
}

BOOL FindingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCard* (*indexes);
	WordCard* wordCard;
	Long current;

	if (HIWORD(wParam) == BN_CLICKED) {
		indexes = (WordCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		current = 0;
		wordCard = indexes[current];
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.example);

		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);
	}
	return TRUE;
}

BOOL FindingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCard* (*indexes);
	WordCard* wordCard;
	Long current;
	if (HIWORD(wParam) == BN_CLICKED) {
		indexes = (WordCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		current = (Long)GetProp(hWnd, "PROP_CURRENT");
		current--;
		if (current < 0) {
			current = 0;
		}
		wordCard = indexes[current];
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.example);
		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);
	}
	return TRUE;
}

BOOL FindingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCard* (*indexes);
	WordCard* wordCard;
	Long current;
	Long count;
	if (HIWORD(wParam) == BN_CLICKED) {
		indexes = (WordCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		count = (Long)GetProp(hWnd, "PROP_COUNT");
		current = (Long)GetProp(hWnd, "PROP_CURRENT");
		current++;
		if (current >= count) {
			current = count - 1;
		}
		wordCard = indexes[current];
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.example);
		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);
	}
	return TRUE;
}

BOOL FindingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCard* (*indexes);
	WordCard* wordCard;
	Long current;
	Long count;
	if (HIWORD(wParam) == BN_CLICKED) {
		indexes = (WordCard * (*))GetWindowLong(hWnd, GWL_USERDATA);
		count = (Long)GetProp(hWnd, "PROP_COUNT");
		current = (Long)GetProp(hWnd, "PROP_CURRENT");
		current = count - 1;
		wordCard = indexes[current];
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard->word.example);
		SetProp(hWnd, "PROP_CURRENT", (HANDLE)current);
	}
	return TRUE;
}