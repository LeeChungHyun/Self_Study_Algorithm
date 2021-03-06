#ifndef _MEMORIZINGFORM_H
#define _MEMORIZINGFORM_H
#include <Windows.h>

BOOL CALLBACK MemorizingFormProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL MemorizingForm_OnInitDialog(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL MemorizingForm_OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL MemorizingForm_OnClose(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL MemorizingForm_OnFirstButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL MemorizingForm_OnPreviousButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL MemorizingForm_OnNextButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL MemorizingForm_OnLastButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL MemorizingForm_OnKeepButtonClicked(HWND hWnd, WPARAM wParam, LPARAM lParam);
#endif // !_MEMORIZINGFORM_H