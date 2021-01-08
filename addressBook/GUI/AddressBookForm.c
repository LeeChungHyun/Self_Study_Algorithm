#include "AddressBookForm.h"
#include "FindingForm.h"
#include "addressBook.h"
#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <CommCtrl.h>
#pragma warning(disable:4996)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	int response;
	response = DialogBox(hInstance, MAKEINTRESOURCE(IDD_ADDRESSBOOKFORM), NULL, AddressBookFormProc);
	return response;
}
//���ν��� �ݹ�
BOOL CALLBACK AddressBookFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BOOL ret = 0;
	switch (message) {
	case WM_INITDIALOG: ret = AddressBookForm_OnInitDialog(hWnd, wParam, lParam); break;
	case WM_COMMAND: ret = AddressBookForm_OnCommand(hWnd, wParam, lParam); break;
	case WM_NOTIFY: ret = AddressBookForm_OnNotify(hWnd, wParam, lParam); break;
	case WM_CLOSE: ret = AddressBookForm_OnClose(hWnd, wParam, lParam); break;
	deafult: ret = FALSE; break;
	}
	return ret;
}
//Ŀ�ǵ�
BOOL AddressBookForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret = 0;
	switch (LOWORD(wParam)) {
	case IDC_BUTTON_RECORD: ret = AddressBookForm_OnRecordButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_FIND: ret = AddressBookForm_OnFindButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_CORRECT: ret = AddressBookForm_OnCorrectButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ERASE: ret = AddressBookForm_OnEraseButtonClicked(hWnd, wParam, lParam); break;
	case IDC_BUTTON_ARRANGE: ret = AddressBookForm_OnArrangeButtonClicked(hWnd, wParam, lParam); break;
	deafult: ret = FALSE; break;
	}
	return ret;
}

//notifyĿ�ǵ�
BOOL AddressBookForm_OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	BOOL ret = 0;
	switch (LOWORD(wParam)) {
	case IDC_LIST_PERSONALS: ret = AddressBookForm_OnListViewDoubleClicked(hWnd, wParam, lParam); break;
	default: ret = FALSE; break;
	}
	return ret;
}

//1. ������ ����
BOOL AddressBookForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	AddressBook* addressBook;
	LVCOLUMN column = { 0, };
	LVITEM item = { 0, };
	Long i = 0;
	Long count;
	TCHAR number[64];

	//1.1 �ּҷ��� �����
	addressBook = (AddressBook*)malloc(sizeof(AddressBook));
	Create(addressBook, 10000);
	SetWindowLong(hWnd, GWL_USERDATA, (Long)addressBook);

	//1.2 �����ϴ�
	count = Load(addressBook);

	//1.3 ����Ʈ�� ��Ʈ���� ����� �����.
	column.mask = LVCF_WIDTH | LVCF_TEXT;

	column.cx = 50;
	column.pszText = "��ȣ";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)0, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "����";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)1, (LPARAM)&column);
	column.cx = 250;
	column.pszText = "�ּ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)2, (LPARAM)&column);
	column.cx = 100;
	column.pszText = "��ȭ��ȣ";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)3, (LPARAM)&column);
	column.cx = 200;
	column.pszText = "�̸����ּ�";
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTCOLUMN, (WPARAM)4, (LPARAM)&column);

	//1.4. ����Ʈ�� ��Ʈ�ѿ� ��ü������ �����Ѵ�.
	SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETEXTENDEDLISTVIEWSTYLE, (WPARAM)0, (LPARAM)LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//1.5 ������ ������ŭ ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��Ѵ�.
	item.mask = LVIF_TEXT;
	while (i < count) {
		sprintf(number, "%d", i + 1);
		item.iItem = i;
		item.iSubItem = 0;
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

		item.iSubItem = 1;
		item.pszText = addressBook->personals[i].name;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = addressBook->personals[i].address;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = addressBook->personals[i].phoneNumber;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = addressBook->personals[i].emailAddress;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);
		i++;
	}
	return TRUE;
}

//2. �����ϱ� ��ư Ŭ����
BOOL AddressBookForm_OnRecordButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	AddressBook* addressBook;
	TCHAR name[11];
	TCHAR address[64];
	TCHAR phoneNumber[12];
	TCHAR emailAddress[64];
	TCHAR number[64];
	Long index = 0;
	LVITEM item = { 0, };

	if (HIWORD(wParam) == BN_CLICKED) {
		//2.1. ������ �д´�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_GETTEXT, (WPARAM)11, (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)emailAddress);

		//2.2. �ּҷϿ��� �����ϴ�.
		addressBook = (AddressBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Record(addressBook, name, address, phoneNumber, emailAddress);

		//2.3. ����Ʈ�� ��Ʈ�ѿ� �׸��� �߰��ϴ�.
		sprintf(number, "%d", index + 1);
	
		item.mask = LVIF_TEXT;
		item.iItem = index;

		item.iSubItem = 0;
		item.pszText = number;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

		item.iSubItem = 1;
		item.pszText = addressBook->personals[index].name;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = addressBook->personals[index].address;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = addressBook->personals[index].phoneNumber;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = addressBook->personals[index].emailAddress;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return TRUE;
}

//3. ã�� ��ư�� Ŭ����
BOOL AddressBookForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	if (HIWORD(wParam) == BN_CLICKED) {
		DialogBox((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDD_FINDINGFORM), NULL, FindingFormProc);
	}
	return TRUE;
}

//4. ��ġ�� ��ư�� Ŭ����
BOOL AddressBookForm_OnCorrectButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	AddressBook* addressBook;
	TCHAR address[64];
	TCHAR phoneNumber[12];
	TCHAR emailAddress[64];
	Long index;
	LVITEM item = { 0, };

	if (HIWORD(wParam) == BN_CLICKED) {
		//4.1. ������ �д�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PHONENUMBER), WM_GETTEXT, (WPARAM)12, (LPARAM)phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILADDRESS), WM_GETTEXT, (WPARAM)64, (LPARAM)emailAddress);

		//4.2. ����Ʈ�� ��Ʈ���� ���õ� �׸��� ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//4.3. �ּҷϿ��� ��ģ��.
		addressBook = (AddressBook*)GetWindowLong(hWnd, GWL_USERDATA);
		index = Correct(addressBook, index, address, phoneNumber, emailAddress);

		//4.4. ����Ʈ�� ��Ʈ���� �׸��� ��ģ��.
		item.mask = LVIF_TEXT;
		item.iItem = index;

		item.iSubItem = 2;
		item.pszText = addressBook->personals[index].address;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = addressBook->personals[index].phoneNumber;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = addressBook->personals[index].emailAddress;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
	}
	return TRUE;
}

//5. ����� ��ư�� Ŭ����
BOOL AddressBookForm_OnEraseButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	AddressBook* addressBook;
	Long index;
	Long erased;
	Long i;
	TCHAR number[64];
	LVITEM item = { 0, };

	if (HIWORD(wParam) == BN_CLICKED) {
		//5.1. ����Ʈ�� ��Ʈ���� ���õ� �׸��� ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//5.2. �ּҷϿ��� �����.
		addressBook = (AddressBook*)GetWindowLong(hWnd, GWL_USERDATA);
		erased = Erase(addressBook, index);
		//5.3. ����Ʈ�� ��Ʈ���� �׸��� �����.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_DELETEITEM, (WPARAM)index, (LPARAM)0);
		//5.4. ���õ� ��ġ���� ������ �ٱ��� ��ȣ�� ��ģ��.
		item.iSubItem = 0;
		i = index;
		while (i < addressBook->length) {
			sprintf(number, "%d", i + 1);
			item.iItem = i;
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)index, (LPARAM)&item);
			i++;
		}
	}
	return TRUE;
}

//6. �����ϱ� ��ư�� Ŭ����
BOOL AddressBookForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	AddressBook* addressBook;
	TCHAR number[64];
	Long i = 0;
	LVITEM item = { 0, };

	if (HIWORD(wParam) == BN_CLICKED) {
		//6.1. �ּҷϿ��� �����ϴ�.
		addressBook = (AddressBook*)GetWindowLong(hWnd, GWL_USERDATA);
		Arrange(addressBook);

		//6.2. ����Ʈ�� ��Ʈ���� ��� �׸��� �����.
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_DELETEALLITEMS, (WPARAM)0, (LPARAM)0);

		//6.3. ����Ʈ�� ��Ʈ�ѿ� �ּҷϿ� ���� ������ŭ �׸��� �߰��Ѵ�.
		item.mask = LVIF_TEXT;
		while (i < addressBook->length) {
			sprintf(number, "%d", i + 1);
			item.iItem = i;

			item.iSubItem = 0;
			item.pszText = number;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_INSERTITEM, (WPARAM)0, (LPARAM)&item);

			item.iSubItem = 1;
			item.pszText = addressBook->personals[i].name;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 2;
			item.pszText = addressBook->personals[i].address;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 3;
			item.pszText = addressBook->personals[i].phoneNumber;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			item.iSubItem = 4;
			item.pszText = addressBook->personals[i].emailAddress;
			SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)&item);

			i++;
		}
	}
	return TRUE;
}

//7. ����Ʈ �� ��Ʈ���� �׸��� ����Ŭ����
BOOL AddressBookForm_OnListViewDoubleClicked(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	TCHAR name[11];
	TCHAR address[64];
	TCHAR phoneNumber[12];
	TCHAR emailAddress[64];
	Long index;
	LVITEM item = { 0, };

	if (((LPNMHDR)lParam)->code == NM_DBLCLK) {
		//7.1. ����Ʈ�� ��Ʈ���� ���õ� ��ġ�� �д´�.
		index = (Long)SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0);

		//7.2. ���õ� ��ġ�� �׸��� �д´�.
		item.mask = LVIF_TEXT;
		item.iItem = index;

		item.iSubItem = 1;
		item.pszText = name;
		item.cchTextMax = 11;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 2;
		item.pszText = address;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 3;
		item.pszText = phoneNumber;
		item.cchTextMax = 12;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		item.iSubItem = 4;
		item.pszText = emailAddress;
		item.cchTextMax = 64;
		SendMessage(GetDlgItem(hWnd, IDC_LIST_PERSONALS), LVM_GETITEMTEXT, (WPARAM)index, (LPARAM)&item);

		//7.3. ���ο� ����Ѵ�.
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_NAME), WM_SETTEXT, (WPARAM)0, (LPARAM)name);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_ADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)address);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_PHONENUMBER), WM_SETTEXT, (WPARAM)0, (LPARAM)phoneNumber);
		SendMessage(GetDlgItem(hWnd, IDC_EDIT_EMAILADDRESS), WM_SETTEXT, (WPARAM)0, (LPARAM)emailAddress);
	}
	return TRUE;
}

//8. �ݱ� ��ư Ŭ����
BOOL AddressBookForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam) {
	AddressBook* addressBook;
	addressBook = (AddressBook*)GetWindowLong(hWnd, GWL_USERDATA);
	if (addressBook != NULL) {
		//8.1 �����Ѵ�.
		Save(addressBook);
		//8.2 �ּҷ��� ���ش�.
		Destroy(addressBook);
		free(addressBook);
	}
	EndDialog(hWnd, 0);
	return TRUE;

}
