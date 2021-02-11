#include "BusinessCardHolder.h"
#include "PuttingOutForm.h"
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
	HWND businessCardHolderForm;
	BusinessCardHolder* businessCardHolder;
	BusinessCard businessCard;
	BusinessCard* index;
	//명함꽂이 윈도우를 찾는다
	businessCardHolderForm = FindWindow("#32770", "명함꽂이");
	businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
	//명함을 꽂는다
	businessCard = PutOut(businessCardHolder, businessCardHolder->current);
	//들어내기 윈도우에 명함을 출력한다
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.address);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.phoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_FAX), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.fax);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_DOMAIN), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.company.domain);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.name);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.phoneNumber);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.emailAddress);
	SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard.personal.position);
	//명함꽂이 윈도우의 명함꽂이에 명함이 있으면 명함곶이 윈도우에 명함을 출력한다.
	if (businessCardHolder->current != NULL) {
		index = businessCardHolder->current;
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.phoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_FAX), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.fax);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_DOMAIN), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.domain);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.phoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
	}
	else{
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_FAX), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_DOMAIN), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)"");
	}
	return TRUE;
}

BOOL PuttingOutForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	int ret;
	BusinessCard businessCard;
	HWND businessCardHolderForm;
	BusinessCardHolder* businessCardHolder;
	BusinessCard* index;

	//2. 닫기 버튼을 클릭했을 때
	//2.1. 메시지 박스를 출력한다.
	ret = MessageBox(hWnd, (LPCWSTR)"끼우시겠습니까?", (LPCWSTR)"알림", MB_YESNOCANCEL | MB_ICONEXCLAMATION);
	switch (ret) {
		//2.2. 예 버튼을 클릭했을 때
	case IDYES:
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_NAME), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_PHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_FAX), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_DOMAIN), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.company.domain);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)businessCard.personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_PHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)businessCard.personal.phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)businessCard.personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_GETTEXT, (WPARAM)16, (LPARAM)businessCard.personal.position);
		businessCard.next = NULL;

		//2.2.1. 명함꽂이 윈도우를 찾는다.
		businessCardHolderForm = FindWindow("#32770", "명함꽂이");
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(businessCardHolderForm, GWL_USERDATA);
		//2.2.2. 명함꽂이 윈도우의 명함첩에 끼운다.
		index = PutIn(businessCardHolder, businessCard);
		//2.2.3. 명함꽂이 윈도우에 명함을 출력한다.
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.phoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_FAX), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.fax);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_COMAPNY_DOMAIN), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.domain);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.phoneNumber);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(businessCardHolderForm, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
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