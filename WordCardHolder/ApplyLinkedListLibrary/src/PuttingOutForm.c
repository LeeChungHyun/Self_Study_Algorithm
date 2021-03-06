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
	//���Բ��� �����츦 ã�´�
	wordCardHolderForm = FindWindow("#32770", "�ܾ�ø");
	wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
	//������ �ȴ´�
	wordCard = PutOut(wordCardHolder, wordCardHolder->current);
	//���� �����쿡 ������ ����Ѵ�
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard.word.spelling);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard.word.wordClass);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard.word.meaning);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)wordCard.word.example);
	//���Բ��� �������� ���Բ��̿� ������ ������ ���԰��� �����쿡 ������ ����Ѵ�.
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
	ret = MessageBox(hWnd, (LPCWSTR)"����ðڽ��ϱ�?", (LPCWSTR)"�˸�", MB_YESNOCANCEL | MB_ICONEXCLAMATION);
	switch (ret) {
		//2.2. �� ��ư�� Ŭ������ ��
	case IDYES:
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTSPELLING), WM_GETTEXT, (WPARAM)64, (LPARAM)wordCard.word.spelling);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTWORDCLASS), WM_GETTEXT, (WPARAM)12, (LPARAM)wordCard.word.wordClass);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTMEANING), WM_GETTEXT, (WPARAM)64, (LPARAM)wordCard.word.meaning);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_INSERTEXAMPLE), WM_GETTEXT, (WPARAM)128, (LPARAM)wordCard.word.example);
		//2.2.1. ���Բ��� �����츦 ã�´�.
		wordCardHolderForm = FindWindow("#32770", "�ܾ�ø");
		wordCardHolder = (WordCardHolder*)GetWindowLong(wordCardHolderForm, GWL_USERDATA);
		//2.2.2. ���Բ��� �������� ����ø�� �����.
		index = PutIn(wordCardHolder, wordCard);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTSPELLING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.spelling);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTWORDCLASS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.wordClass);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTMEANING), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.meaning);
		SendMessage(GetDlgItem(wordCardHolderForm, IDC_STATIC_INSERTEXAMPLE), WM_SETTEXT, (WPARAM)0, (LPARAM)index->word.example);
		//2.2.4. ���� �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
		break;
		//2.3. �ƴϿ� ��ư�� Ŭ������ ��
	case IDNO:
		//2.3.1. ���� �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
		break;
	default:
		break;
	}
	return TRUE;
}