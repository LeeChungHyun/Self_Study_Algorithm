#include "BusinessCardHolderForm.h"
#include "BusinessCardHolder.h"
#include "FindingForm.h"
#include "PuttingInForm.h"
#include "PuttingOutForm.h"
#include "resource.h"
#include <stdlib.h>
#include <commctrl.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	int response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_BUSINESSCARDHOLDERFORM), NULL, BusinessCardHolderFormProc);

	return response;
}

BOOL CALLBACK BusinessCardHolderFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (message) {
	case WM_INITDIALOG: ret = BusinessCardHolderForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = BusinessCardHolderForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = BusinessCardHolderForm_OnClose(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}

	return ret;
}

BOOL BusinessCardHolderForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardHolder* businessCardHolder;
	Long count;
	BusinessCard* index;
	//1. 윈도우가 생성될 때
	//1.1. 명함첩을 생성하다.
	businessCardHolder = (BusinessCardHolder*)malloc(sizeof(BusinessCardHolder));
	BusinessCardHolder_Create(businessCardHolder);
	SetWindowLong(hWnd, GWL_USERDATA, (LONG)businessCardHolder);
	//명함꽂이를 적재한다.
	count = Load(businessCardHolder);

	//적재할때 첫번째 명함을 보이도록 한다.
	if (count > 0) {
		index = BusinessCardHolder_First(businessCardHolder);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_FAX), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_DOMAIN), WM_SETTEXT, (WPARAM)0, (LPARAM)index->company.domain);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)index->personal.position);
	}
	return TRUE;
}

BOOL BusinessCardHolderForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret;

	switch (LOWORD(wParam)) {
	case IDC_BUTTON_PUTIN: ret = BusinessCardHolderForm_OnPutInButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIND: ret = BusinessCardHolderForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PUTOUT: ret = BusinessCardHolderForm_OnPutOutButtonClicked(hWnd, wParam, lParam); break;
	//case IDC_BUTTON_ARRANGE: ret = BusinessCardHolderForm_OnArrangeButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIRST: ret = BusinessCardHolderForm_OnFirstButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_PREVIOUS: ret = BusinessCardHolderForm_OnPreviousButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_NEXT: ret = BusinessCardHolderForm_OnNextButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_LAST: ret = BusinessCardHolderForm_OnLastButtonClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}

	return ret;
}

BOOL BusinessCardHolderForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardHolder* businessCardHolder;

	//10. 닫기 버튼을 클릭했을 때

	//10.1. 명함첩을 지우다.
	businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
	if (businessCardHolder != NULL) {
		//명함꽂이를 저장한다.
		Save(businessCardHolder);
		BusinessCardHolder_Destroy(businessCardHolder);
		free(businessCardHolder);
	}
	//10.2. 윈도우를 닫다.
	EndDialog(hWnd, 0);

	return TRUE;
}

BOOL BusinessCardHolderForm_OnPutInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//2. 끼우기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1. 끼우기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_PUTTINGINFORM), NULL, PuttingInFormProc);
	}

	return TRUE;
}

BOOL BusinessCardHolderForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//3. 찾기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//3.1. 찾기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), NULL, FindingFormProc);
	}

	return TRUE;
}

BOOL BusinessCardHolderForm_OnPutOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	//4. 들어내기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		//4.1. 들어내기 윈도우를 출력한다.
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_PUTTINGOUTFORM), NULL, PuttingOutFormProc);
	}
	return TRUE;
}
#if 0
BOOL BusinessCardHolderForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardHolder* businessCardHolder;
	BusinessCard* businessCard;

	//5. 정리하기 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		//5.1. 명함첩에서 정리하다.
		Arrange(businessCardHolder);
		//5.2. 명함첩에서 처음으로 이동한다.
		businessCard = First(businessCardHolder);
		//5.3. 명함을 출력한다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_FAX), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_DOMAIN), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.domain);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.position);
	}
	return TRUE;
}
#endif
BOOL BusinessCardHolderForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardHolder* businessCardHolder;
	BusinessCard* businessCard;

	//6. 처음 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		//6.1. 명함첩에서 처음으로 이동하다.
		businessCard = BusinessCardHolder_First(businessCardHolder);
		//6.2. 명함을 출력하다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_FAX), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_DOMAIN), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.domain);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.position);
	}
	return TRUE;
}

BOOL BusinessCardHolderForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardHolder* businessCardHolder;
	BusinessCard* businessCard;

	//7. 이전 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		//7.1. 명함첩에서 이전으로 이동하다.
		businessCard = BusinessCardHolder_Previous(businessCardHolder);
		//7.2. 명함을 출력하다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_FAX), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_DOMAIN), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.domain);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.position);
	}

	return TRUE;
}

BOOL BusinessCardHolderForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardHolder* businessCardHolder;
	BusinessCard* businessCard;

	//8. 다음 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		//8.1. 명함첩에서 다음으로 이동하다.
		businessCard = BusinessCardHolder_Next(businessCardHolder);
		//8.2. 명함을 출력하다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_FAX), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_DOMAIN), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.domain);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.position);
	}

	return TRUE;
}

BOOL BusinessCardHolderForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BusinessCardHolder* businessCardHolder;
	BusinessCard* businessCard;

	//9. 마지막 버튼을 클릭했을 때
	if (HIWORD(wParam) == BN_CLICKED) {
		businessCardHolder = (BusinessCardHolder*)GetWindowLong(hWnd, GWL_USERDATA);
		//9.1. 명함첩에서 마지막으로 이동하다.
		businessCard = BusinessCardHolder_Last(businessCardHolder);
		//9.2. 명함을 출력하다.
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.address);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_FAX), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.fax);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_COMAPNY_DOMAIN), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->company.domain);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.name);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.emailAddress);
		SendMessage(GetDlgItem(hWnd, IDC_STATIC_PERSONAL_POSITION), WM_SETTEXT, (WPARAM)0, (LPARAM)businessCard->personal.position);
	}

	return TRUE;
}