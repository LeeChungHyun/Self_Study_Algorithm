#ifndef _KEEPINGFORM_H
#define _KEEPINGFORM_H
#include <Windows.h>

BOOL CALLBACK KeepingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL KeepingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL KeepingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL KeepingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL KeepingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL KeepingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL KeepingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL KeepingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL KeepingForm_OnGetOutButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
#endif // !_KEEPINGFORM_H