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

	TCHAR positionTypes[][8] = { "인턴", "연구원", "대리", "선임", "과장", "책임", "부장", "본부장", "수석" };
	Long i;

	//1. 끼우기 윈도우가 생성될 때
	//1.1. 직책 목록을 만든다.
	for (i = 0; i < sizeof(positionTypes) / sizeof(positionTypes[0]); i++) {
		SendMessage(GetDlgItem(hWnd, IDC_COMBO_PERSONAL_POSITION), CB_ADDSTRING, (WPARAM)0, (LPARAM)positionTypes[i]);
	}
	//1.2. 도메인 목록을 만든다.
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
	//4. 닫기 버튼을 클릭했을 때
	//4.1. 끼우기 윈도우를 닫다.
	EndDialog(hWnd, 0);

	return TRUE;
}

BOOL PuttingInForm_OnCompanyNameLostFocus(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR companyName[64];
	HWND businessCardHolderForm;
	BusinessCardHolder* businessCardHolder;
	BusinessCard* businessCard = NULL;

	//2. 상호 에딧의 포커스를 잃었을 때
	if (HIWORD(wParam) == EN_KILLFOCUS) {
		//2.1. 상호를 읽는다.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_COMPANY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)companyName);
		//2.2. 명함첩 윈도우를 찾는다.
		businessCardHolderForm = FindWindow("#32770", "명함꽂이");
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
		//2.3. 명함첩 윈도우의 명함첩에서 찾는다.
		businessCard = FindByCompanyName(businessCardHolder, companyName);
		//2.4. 찾았으면 회사를 출력한다.
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

	//3. 끼우기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1. 명함을 읽는다.
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

		//3.2. 명함첩 윈도우를 찾는다.
		businessCardHolderForm = FindWindow("#32770", "명함꽂이");
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
		//3.3. 명함첩 윈도우의 명함첩에 끼운다.
		index = PutIn(businessCardHolder, businessCard);
		//3.4. 명함첩 윈도우에 명함을 출력한다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.phoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_FAX), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.fax);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_DOMAIN), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.domain);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.phoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
		//3.5. 끼우기 윈도우를 닫는다.
		EndDialog(hWnd, 0);
	}

	return TRUE;
}