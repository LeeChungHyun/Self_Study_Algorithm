#ifndef _WORDCARDHOLDERFORM_H
#define _WORDCARDHOLDERFORM_H
#include <Windows.h>

BOOL CALLBACK WordCardHolderFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL WordCardHolderForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordCardHolderForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordCardHolderForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordCardHolderForm_OnPutInButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordCardHolderForm_OnFindButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordCardHolderForm_OnPutOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
//BOOL WordCardHolderForm_OnArrangeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordCardHolderForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordCardHolderForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordCardHolderForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordCardHolderForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordCardHolderForm_OnMemorizeButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordCardHolderForm_OnKeepButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL WordCardHolderForm_OnTestButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
#endif // !_WORDCARDHOLDERFORM_H