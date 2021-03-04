#include "BusinessCardHolder.h"
#include "PuttingInForm.h"
#include "resource.h"
#include <stdio.h> //sprintf
#pragma warning(disable:4996)

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

	TCHAR positionTypes[][8] = { "����", "������", "�븮", "����", "����", "å��", "����", "������", "����" };
	Long i;

	//1. ����� �����찡 ������ ��
	//1.1. ��å ����� �����.
	for (i = 0; i < sizeof(positionTypes) / sizeof(positionTypes[0]); i++) {
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_POSITION), CB_ADDSTRING, (WPARAM)0, (LPARAM)positionTypes[i]);
	}
	//1.2. ������ ����� �����.
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_DOMAIN), CB_ADDSTRING, (WPARAM)0, (LPARAM)"naver.com");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_DOMAIN), CB_ADDSTRING, (WPARAM)0, (LPARAM)"daum.net");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_DOMAIN), CB_ADDSTRING, (WPARAM)0, (LPARAM)"google.com");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_DOMAIN), CB_ADDSTRING, (WPARAM)0, (LPARAM)"empass.net");
	SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_DOMAIN), CB_ADDSTRING, (WPARAM)0, (LPARAM)"yahoo.com");

	return TRUE;
}

BOOL PuttingInForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_EDIT_COMPANY_NAME: ret = PuttingInForm_OnCompanyNameLostFocus(hWnd, wParam, lParam); break;
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

BOOL PuttingInForm_OnCompanyNameLostFocus(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR companyName[64];
	HWND businessCardHolderForm;
	BusinessCardHolder* businessCardHolder;
	BusinessCard* businessCard = NULL;

	//2. ��ȣ ������ ��Ŀ���� �Ҿ��� ��
	if (HIWORD(wParam) == EN_KILLFOCUS) {
		//2.1. ��ȣ�� �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)companyName);
		//2.2. ����ø �����츦 ã�´�.
		businessCardHolderForm = FindWindow("#32770", "���Բ���");
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
		//2.3. ����ø �������� ����ø���� ã�´�.
		businessCard = FindByCompanyName(businessCardHolder, companyName);
		//2.4. ã������ ȸ�縦 ����Ѵ�.
		if (businessCard != NULL) {
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.address);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.phoneNumber);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_FAX), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.fax);
			SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_DOMAIN), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.domain);
		}
	}
	return TRUE;
}

BOOL PuttingInForm_OnPutInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCard businessCard;
	TCHAR id[64];
	TCHAR domain[64];
	HWND businessCardHolderForm;
	BusinessCardHolder* businessCardHolder;
	BusinessCard* index;

	//3. ����� ��ư�� Ŭ������ ��
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1. ������ �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_PHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_FAX), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_DOMAIN), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.domain);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_PHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PERSONAL_ID), WM_GETTEXT, (WPARAM)64, (LPARAM)id);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_DOMAIN), WM_GETTEXT, (WPARAM)64, (LPARAM)domain);
		sprintf(businessCard.personal.emailAddress, "%s@%s", id, domain);
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_POSITION), WM_GETTEXT, (WPARAM)16, (LPARAM)businessCard.personal.position);

		//3.2. ����ø �����츦 ã�´�.
		businessCardHolderForm = FindWindow("#32770", "���Բ���");
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
		//3.3. ����ø �������� ����ø�� �����.
		index = PutIn(businessCardHolder, businessCard);
		//3.4. ����ø �����쿡 ������ ����Ѵ�.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.phoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_FAX), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.fax);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_DOMAIN), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.domain);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.phoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		//3.5. ����� �����츦 �ݴ´�.
		EndDialog(hWnd, 0);
	}

	return TRUE;
}