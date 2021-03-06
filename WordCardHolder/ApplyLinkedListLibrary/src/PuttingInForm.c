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
	TCHAR wordClassTypes[][8] = { "���", "����", "����", "�����", "�λ�", "��ġ��", "���ӻ�", "��ź��" };
	Long i;

	//1. ����� �����찡 ������ ��
	//1.1. ��å ����� �����.
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
	//4. �ݱ� ��ư�� Ŭ������ ��
	//4.1. ����� �����츦 �ݴ�.
	EndDialog(hWnd, 0);

	return TRUE;
}

BOOL PuttingInForm_OnPutInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	WordCard wordCard;
	HWND wordCardHolderForm;
	WordCardHolder* wordCardHolder;
	WordCard* index;

	//3. ����� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1. ������ �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_SPELLING), WM_GETTEXT, (WPARAM)64, (LPARAM)wordCard.word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_WORDCLASS), WM_GETTEXT, (WPARAM)11, (LPARAM)wordCard.word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_MEANING), WM_GETTEXT, (WPARAM)64, (LPARAM)wordCard.word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EXAMPLE), WM_GETTEXT, (WPARAM)128, (LPARAM)wordCard.word.example);

		//3.2. ����ø �����츦 ã�´�.
		wordCardHolderForm = FindWindow("#32770", "�ܾ�ø");
		wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
		//3.3. ����ø �������� ����ø�� �����.
		index = PutIn(wordCardHolder, wordCard);
		//3.4. ����ø �����쿡 ������ ����Ѵ�.
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.spelling);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.wordClass);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.meaning);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.example);
		//3.5. ����� �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
	}
	return TRUE;
}